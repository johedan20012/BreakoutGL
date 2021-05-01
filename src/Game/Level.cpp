#include "Level.h"

Player* Level::player = nullptr; 

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

        float freq = 8;

        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noise.SetSeed((int)time(NULL));

        for(unsigned int i = 0; i<noRows; i++){
            std::vector<unsigned int> row;
            for(int j=0; j<noColumns; j++){
                float x = factorX * j;
                float y = factorY * i;
                
                glm::vec2 p (x*freq,y*freq);
                float result = (noise.GetNoise(p.x,p.y) +1.0f)/2.0f; //result \in [0,1]
                result = result*10-4;
                int code = (int)result; 

                if(code > 5) code = 5;
                if(code < 0) code = 0;
                row.push_back(code);
            }
            tileData.push_back(row);
        }
    }else{
        //Poner semillas
        int noSeeds = 1;
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
                    int taxiDistance = abs(j-seeds[k].x)+abs(i-seeds[k].y);
                    int newCode = 5-taxiDistance;
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

    powerUp.update(deltaTime);

    ball.update(deltaTime, 800.0f,600.0f);

    ballParticles.update(ball,deltaTime);

    for(int i =0; i<NUM_LASERS; i++){
        lasers[i].update(deltaTime);
    }

    handleCollisions();

    for(int i = bricks.size()-1; i>=0; i--){
           if(bricks[i].isDestroyed()){
               noBricks--;
               bricks.erase(bricks.begin()+i);
           } 
    }

    if(ball.isDead()){
        player->loseLive();
        if(!player->gameover())
            ball.reset(364.0f);
    }
}

void Level::render(Shader& shader){

    ballParticles.render(shader);

    for(int  i = 0; i<bricks.size(); i++){
        bricks[i].render(shader);
        //bricks[i].getHitbox().render(shader);
    }

    for(int i =0; i<NUM_LASERS; i++){
        if(!lasers[i].isActive()) continue;
        lasers[i].render(shader);
    }

    player->render(shader);
    //player.getHitbox().render(shader);

    ball.render(shader);
    //ball.getHitbox().render(shader);
    if(powerUp.isActive()){
        powerUp.render(shader);
    }
}

bool Level::isCompleted(){
    return (noBricks <= 0);
}

void Level::handleInput(){
    if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        ball.setStuck(false);
    }
    if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && player->hasLasers()){
        int laser1 = -1,laser2 = -1;
        for(int i=0; i<NUM_LASERS; i++){
            if(!lasers[i].isActive()){
                if(laser1 == -1){
                    laser1 = i;
                }else{
                    laser2 = i;
                    break;
                }
            }
        }
        if(laser2 != -1){
            lasers[laser1].launch(player->getPosition()+glm::vec2(0.0f,-15.0f));
            lasers[laser2].launch(player->getPosition()+glm::vec2(player->getSize().x-20.0f,0.0f));
        }
    }
}

void Level::handleCollisions(){
    if(!ball.isStuck() && !ball.isDead()){
        for(int i=0; i<bricks.size(); i++){
            if(Physics::BoxCircleCollision(bricks[i].getHitbox(),ball.getHitbox())){
                bricks[i].hit();
                if(bricks[i].isDestroyed() && !powerUp.isActive()){ //Trata de generar un modificador con tipo aleatorio
                    int value = rand()%2; // 1 de cada 6 genera un modificador
                    if(value == 0){
                        ModifierType type =(ModifierType)(rand()%7);// (ModifierType)(rand()%(int)(ModifierType::NUM_TYPES)); //Randomiza el tipo de mofi
                    
                        powerUp = Modifier(bricks[i].getPosition(),glm::vec2(50.0f,175.0f),type,SpriteManager::getSprite("pow"+std::to_string((int)(type)+1)));
                    }
                }
                ball.hitBrick(bricks[i].getHitbox());
            }
        }
    }

    if(!ball.isStuck() && !ball.isDead()){
        if(Physics::BoxCircleCollision(player->getHitbox(),ball.getHitbox())){
            ball.hitPlayer();
        }
    }

    if(powerUp.isActive()){
        if(Physics::BoxBoxCollision(player->getHitbox(),powerUp.getHitbox())){
            powerUp.desactivate();
            player->applyModifier(powerUp.getType());
            ball.applyModifier(powerUp.getType());
        }
    }
    
    for(int i=0; i<NUM_LASERS; i++){
        if(lasers[i].isActive()){
            for(int j=0; j<bricks.size(); j++){
                if(bricks[j].isDestroyed()) continue;
                if(Physics::BoxBoxCollision(bricks[j].getHitbox(),lasers[i].getHitbox())){
                    bricks[j].hit();

                    lasers[i].hit();
                }
            }
        }
    }
}


void Level::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight){
    noBricks  = 0;
    unsigned int noRows = tileData.size();
    unsigned int noColumns = tileData[0].size();
    float unitWidth = levelWidth; 
    unitWidth /=  noColumns;
    float unitHeight = levelHeight;
    unitHeight /= noRows;
    for(int i = 0; i<noRows; i++){
        for(int j= 0; j<noColumns; j++){
            if(tileData[i][j]==5){ //Labrillo solido
                bricks.push_back(Brick(glm::vec2(unitWidth*j,unitHeight*i),
                                       glm::vec2(unitWidth,unitHeight),
                                       //glm::vec4(0.8f,0.8f,0.7f,1.0f),
                                       glm::vec4(1.0f,1.0f,1.0f,1.0f),
                                       SpriteManager::getSprite("block_solid"),
                                       true));
            }else if(tileData[i][j]>=1){
                noBricks ++;

                glm::vec2 pos(unitWidth*j,unitHeight*i);
                glm::vec2 size(unitWidth,unitHeight);

                glm::vec4 color(1.0f);
                switch (tileData[i][j]){
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
                bricks.push_back(Brick(pos,size,color,SpriteManager::getSprite("block")));
            } //else no se agrega un ladrillo en esa posicion
        }
    }

    //Iniciar jugador
    Ball::setPlayer(player);

    //Iniciar pelota
    glm::vec2 ballPosition = player->getPosition()+glm::vec2(player->getSize().x/2.0f - 12.5f,-25.0f);
    ball = Ball(ballPosition,364.0f,SpriteManager::getSprite("ball"));

    //Inicia el generador de particulas
    ballParticles = ParticleGenerator(glm::vec2(10.0f,10.0f),250,SpriteManager::getSprite("particle"));

    //Inicia a los lasers
    Laser::setPlayer(player);
    for(int  i=0; i<NUM_LASERS; i++){
        lasers[i] = Laser(SpriteManager::getSprite("laser"));
    }
}

void Level::setPlayer(Player* p){
    player = p;
}