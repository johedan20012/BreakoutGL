#include "Level.h"

Player* Level::player = nullptr; 

const int Level::MOV[4][2]  = {
                            {1,0},
                            {0,1},
                            {-1,0},
                            {0,-1}
                        };

Level::~Level(){
    for(int  i = 0; i<bricks.size(); i++){
        for(int j = 0; j<bricks[i].size(); j++){
            if(bricks[i][j] != nullptr){
                delete bricks[i][j];
                bricks[i][j] = nullptr;
            }
        }
        bricks[i].clear();
    }
    bricks.clear();

    for(unsigned int i = 0; i<balls.size(); i++){
        delete balls[i];
        balls[i] = nullptr;
    }
    balls.clear();

    delete powerUp;
    powerUp = nullptr;
}

void Level::load(const char* filename,unsigned int levelWidth,unsigned int levelHeight,TextFont& fuente){
    this->fuente = fuente;
    
    std::ifstream file;
    std::string line;
    std::vector<std::vector<unsigned int>>tileData;
    unsigned int tileCode;
    file.open(filename);

    if(file.is_open()){
        while(std::getline(file,line)){
            std::vector<unsigned int> row;
            std::istringstream sstream(line);
            while(sstream >> tileCode){
                row.push_back(tileCode);
            }
            tileData.push_back(row);
        }
        if(tileData.size() > 0){
            init(tileData,levelWidth,levelHeight);
        }
    }else{
        std::cout<<"No se pudo cargar el nivel:"<<filename<<"\n";
    }
    file.close();
}

void Level::load(unsigned int noRows,unsigned int noColumns,unsigned int levelWidth,unsigned int levelHeight,TextFont& fuente,bool noise){
    this->fuente = fuente;
    std::vector<std::vector<unsigned int>>tileData;
    unsigned int tileCode;

    if(noise){
        float factorX = 1.0f / (noColumns - 1);
        float factorY = 1.0f / (noRows-1);

        int a = 1,b=2;
        //float freq = 8;

        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noise.SetSeed((int)time(NULL));

        for(unsigned int i = 0; i<noRows; i++){
            std::vector<unsigned int> row;
            for(int j=0; j<noColumns; j++){
                float x = factorX * j;
                float y = factorY * i;
                float sum = 0.0f;
                float freq = a;
                float scale = b;

                for( int oct = 0; oct < 4; oct++ ) {
                    glm::vec2 p(x * freq, y * freq);
                    float val = noise.GetNoise(p.x,p.y) / scale;
                    sum += val;
                    
                    
                    freq *= 2.0f; 
                    scale *= b; 
                }

                float result = (sum + 1.0f)/ 2.0f;
                result = result*6-1;
                int code = (int)result; 

                if(code > 5) code = 5;
                if(code < 0) code = 0;
                row.push_back(code);
                /*
                glm::vec2 p (x*freq,y*freq);
                float result = (noise.GetNoise(p.x,p.y) +1.0f)/2.0f; //result \in [0,1]
                result = result*10-4;
                int code = (int)result; 

                if(code > 5) code = 5;
                if(code < 0) code = 0;
                row.push_back(code);*/
            }
            tileData.push_back(row);
        }
    }else{
        //Poner semillas
        int noSeeds = 4;
        std::vector<glm::vec2> seeds; 
        for(int i = 0; i<noSeeds; i++){
            seeds.push_back(glm::vec2((float)(rand()%noColumns),(float)(rand()%noRows)));
        }
        //Poner los datos en la matriz
        for(int i = 0; i<noRows; i++){
            std::vector<unsigned int> row;
            for(int j = 0; j<noColumns; j++){
                unsigned int code = 0;
                for(int k = 0; k<noSeeds; k++){
                    //Calcula la taxi-distancia de la casilla (j,i) a la k-esima semilla
                    int newCode = 5-MathHelper::taxiDistance(glm::vec2(j,i),seeds[k]);
                    if(newCode < 0) newCode = 0;
                    if(newCode > code){
                        code = newCode;
                    }
                }

                row.push_back(code);
            }
            tileData.push_back(row);
        }
    }

    init(tileData,levelWidth,levelHeight);
}

void Level::update(float deltaTime){
    handleInput();

    player->update(deltaTime);

    if(powerUp != nullptr) powerUp->update(deltaTime);

    for(int i = 0; i<balls.size(); i++){
        balls[i]->update(deltaTime,800.0f,600.0f);
    }
    
    PhysicsManager::update();

    for(int i = 0; i<bricks.size(); i++){
        for(int j = 0; j<bricks[i].size(); j++){
            if(bricks[i][j] != nullptr){
                if(bricks[i][j]->isDestroyed()){
                    if(bricks[i][j]->shouldSpawnModifier()){
                        spawnModifier(bricks[i][j]->getPosition());
                    }
                    if(bricks[i][j]->shouldExplode()){
                        for(int k=0; k<4; k++){
                            int aux = i+MOV[k][0],auy=j+MOV[k][1];
                            if( aux>=0 && aux<bricks.size() && auy >= 0 && auy<bricks[0].size()){
                                if(bricks[aux][auy] != nullptr){
                                    if(!bricks[aux][auy]->isDestroyed()){
                                        bricks[aux][auy]->destroy();
                                    }
                                }
                            }
                        }      
                    }
                    noBricks--;
                    delete bricks[i][j];
                    bricks[i][j] = nullptr;
                } 
            }
        }
    }


    for(int i = balls.size()-1; i>=0; i--){
        if(balls[i]->isDead()){
            delete balls[i];
            balls.erase(balls.begin()+i);
        }
    }

    if(powerUp != nullptr){
        if(!powerUp->isActive()){
            if(powerUp->shouldApplyEffect()){
                applyModifier(powerUp->getModType());
            }
            delete powerUp;
            powerUp = nullptr;
        }
    }

    if(balls.size() == 0){
        player->loseLive();
        if(!player->gameover()){
            //ball->reset(364.0f);
            spawnBall();
        }
    }
}

void Level::render(Shader& shader){

    //ballParticles.render(shader);

    for(int  i = 0; i<bricks.size(); i++){
        for(int j = 0; j<bricks[i].size(); j++){
            if(bricks[i][j] != nullptr) bricks[i][j]->render(shader);
        }
        //bricks[i].getHitbox().render(shader);
    }

    player->render(shader);
    //player.getHitbox().render(shader);

    for(int i = 0; i<balls.size(); i++){
        balls[i]->render(shader);
    }
    //ball.getHitbox().render(shader);
    if(powerUp != nullptr){
        if(powerUp->isActive()){
            powerUp->render(shader);
        }
    }
}

bool Level::isCompleted(){
    return (noBricks <= 0) || finished;
}

// ==================== Funciones para los objetos del juego =========================
void Level::spawnModifier(glm::vec2 pos){
    ModifierType type =(ModifierType)(rand()%13);
    if(powerUp != nullptr){
        if(powerUp->isActive()){
           return; 
        }
        if(powerUp->shouldApplyEffect()){
            applyModifier(powerUp->getModType());
        }
        delete powerUp;
    }
    powerUp = new Modifier(pos,glm::vec2(50.0f,175.0f),type,SpriteManager::getSprite("pow"+std::to_string((int)(type)+1)));
}

void Level::applyModifier(ModifierType modType){
    switch (modType){
        case ModifierType::EXTRA_BALL:
            spawnBall();
            return;
        
        case ModifierType::REMOVE_BALL:
            if(balls.size() >0){
                delete balls[balls.size()-1];
                balls.erase(balls.begin()+balls.size()-1);
            }
            return;
        
        case ModifierType::NEXT_LEVEL:
            finished = true;
            return;
    }

    for(int i = 0; i<balls.size(); i++){
        balls[i]->applyModifier(modType);
    }
    player->applyModifier(modType);
}

void Level::handleInput(){
    if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        for(int i = 0; i<balls.size(); i++){
            balls[i]->setStuck(false);
        }
        
    }
}

void Level::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight){
    //Resetea el manejador de fisicas
    
    noBricks  = 0;
    unsigned int noRows = tileData.size();
    unsigned int noColumns = tileData[0].size();
    float unitWidth = levelWidth; 
    unitWidth /=  noColumns;
    float unitHeight = levelHeight;
    unitHeight /= noRows;
    for(int i = 0; i<noColumns; i++){
        std::vector<Brick*> column;
        for(int j= 0; j<noRows; j++){
            Brick* newBrick = nullptr;
            if(tileData[j][i]==5){ //Labrillo solido
                newBrick = new Brick(glm::vec2(unitWidth*i,unitHeight*j),
                                       glm::vec2(unitWidth,unitHeight),
                                       //glm::vec4(0.8f,0.8f,0.7f,1.0f),
                                       glm::vec4(1.0f,1.0f,1.0f,1.0f),
                                       SpriteManager::getSprite("block_solid"),
                                       true);
            }else if(tileData[j][i]>=1){
                noBricks ++;

                glm::vec2 pos(unitWidth*i,unitHeight*j);
                glm::vec2 size(unitWidth,unitHeight);

                glm::vec4 color(1.0f);
                switch (tileData[j][i]){
                    case 1:
                        //color = glm::vec4(0.2f, 0.6f, 1.0f,1.0f);
                        color = glm::vec4(0.2f,0.2f,0.2f,1.0f);
                        break;
                    case 2:
                        //color = glm::vec4(0.0f, 0.7f, 0.0f,1.0f);
                        color = glm::vec4(0.4f,0.4f,0.4f,1.0f);
                        break;
                    case 3:
                        //color = glm::vec4(0.8f, 0.8f, 0.4f,1.0f);
                        color = glm::vec4(0.6f,0.6f,0.6f,1.0f);
                        break;
                    case 4:
                        //color = glm::vec4(1.0f, 0.5f, 0.0f,1.0f);
                        color = glm::vec4(0.8f,0.8f,0.8f,1.0f);
                        break;
                }
                newBrick = new Brick(pos,size,color,SpriteManager::getSprite("block"));
            } //else no se crea un ladrillo en esta posicion
            column.push_back(newBrick);
        }
        bricks.push_back(column);
    }
    //Iniciar jugador
    Ball::setPlayer(player);
    
    //Iniciar pelota
    for(int i = 0; i<10; i++){
        spawnBall();
    }
}

void Level::spawnBall(){
    glm::vec2 ballPosition = player->getPosition()+glm::vec2(player->getSize().x/2.0f - 12.5f,-25.0f);
    balls.push_back(new Ball(ballPosition,364.0f,SpriteManager::getSprite("ball")));
}

void Level::setPlayer(Player* p){
    player = p;
}