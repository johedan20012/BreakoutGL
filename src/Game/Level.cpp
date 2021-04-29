#include "Level.h"

Level::Level(){}

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



void Level::update(float deltaTime){
    handleInput();

    player.update(deltaTime);

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
        player.loseLive();
        if(!player.gameover())
            ball.reset(364.0f);
    }
}

void Level::render(Shader& shader){

    ballParticles.render(shader);
    
    /*glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(400.0f,300.0f,0.0f));

    //view = glm::translate(view, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); //Esto traslada el centro del objeto a la mitad del mismo, asi el objeto rota sobre su propio centro
    view = glm::rotate(view, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
    //view = glm::translate(view, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); //Devuelve todo a como estaba
    view = glm::translate(view, glm::vec3(-400.0f,-300.0f,0.0f));
    shader.setFloatMat4("view",view); */

    for(int  i = 0; i<bricks.size(); i++){
        bricks[i].render(shader);
        //bricks[i].getHitbox().render(shader);
    }

    //shader.setFloatMat4("view",glm::mat4(1.0f));

    for(int i =0; i<NUM_LASERS; i++){
        if(!lasers[i].isActive()) continue;
        lasers[i].render(shader);
    }

    player.render(shader);
    //player.getHitbox().render(shader);

    ball.render(shader);
    //ball.getHitbox().render(shader);
    if(powerUp.isActive()){
        powerUp.render(shader);
    }

    //Renderizar los puntos y vidas del jugador
    std::stringstream ss,ss2; ss << player.getLives();
    fuente.renderText("Vidas: "+ss.str(),glm::vec2(5.0f,5.0f),1.0f,ShaderManager::getShader("textShader"));
    ss2<<player.getScore();
    fuente.renderText("Puntos: "+ss2.str(),glm::vec2(600.0f,5.0f),1.0f,ShaderManager::getShader("textShader")); //Si alguien ve esto no lo replique porfavor esta mal
}

bool Level::isCompleted(){
    return noBricks <= 0 || player.gameover();
}

void Level::handleInput(){
    if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        ball.setStuck(false);
    }
    if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && player.hasLasers()){
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
            lasers[laser1].launch(player.getPosition()+glm::vec2(0.0f,-15.0f));
            lasers[laser2].launch(player.getPosition()+glm::vec2(player.getSize().x-20.0f,0.0f));
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
        if(Physics::BoxCircleCollision(player.getHitbox(),ball.getHitbox())){
            ball.hitPlayer();
        }
    }

    if(powerUp.isActive()){
        if(Physics::BoxBoxCollision(player.getHitbox(),powerUp.getHitbox())){
            powerUp.desactivate();
            player.applyModifier(powerUp.getType());
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
    player = Player(SpriteManager::getSprite("bar"));
    Ball::setPlayer(&player);

    //Iniciar pelota
    glm::vec2 ballPosition = player.getPosition()+glm::vec2(player.getSize().x/2.0f - 12.5f,-25.0f);
    ball = Ball(ballPosition,364.0f,SpriteManager::getSprite("ball"));

    //Inicia el generador de particulas
    ballParticles = ParticleGenerator(glm::vec2(10.0f,10.0f),250,SpriteManager::getSprite("particle"));

    //Inicia a los lasers
    Laser::setPlayer(&player);
    for(int  i=0; i<NUM_LASERS; i++){
        lasers[i] = Laser(SpriteManager::getSprite("laser"));
    }
}