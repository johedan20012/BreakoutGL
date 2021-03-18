#include "Level.h"

Level::Level(){}

void Level::load(const char* filename,unsigned int levelWidth,unsigned int levelHeight){
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

    ball.update(deltaTime, 800.0f,600.0f);
}

void Level::render(Shader& shader){
    for(int  i = 0; i<bricks.size(); i++){
        bricks[i].render(shader);
    }

    player.render(shader);

    ball.render(shader);
}

bool Level::isCompleted(){
    return !(bricks.size() > 0);
}

void Level::handleInput(){
    if(Keyboard::keyWentDown(GLFW_KEY_SPACE) == GLFW_PRESS){
        ball.setStuck(false);
    }
}

void Level::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight){
    unsigned int noRows = tileData.size();
    unsigned int noColumns = tileData[0].size();
    float unitWidth = levelWidth; 
    unitWidth /=  noColumns;
    float unitHeight = levelHeight;
    unitHeight /= noRows;
    for(int i = 0; i<noRows; i++){
        for(int j= 0; j<noColumns; j++){
            if(tileData[i][j]==1){ //Labrillo solido
                bricks.push_back(Brick(glm::vec2(unitWidth*j,unitHeight*i),
                                       glm::vec2(unitWidth,unitHeight),
                                       glm::vec3(0.8f,0.8f,0.7f),
                                       SpriteManager::getSprite("block_solid"),
                                       true));
            }else if(tileData[i][j]>1){
                glm::vec2 pos(unitWidth*j,unitHeight*i);
                glm::vec2 size(unitWidth,unitHeight);

                glm::vec3 color(1.0f);
                switch (tileData[i][j]){
                    case 2:
                        color = glm::vec3(0.2f, 0.6f, 1.0f);
                        break;
                    case 3:
                        color = glm::vec3(0.0f, 0.7f, 0.0f);
                        break;
                    case 4:
                        color = glm::vec3(0.8f, 0.8f, 0.4f);
                        break;
                    case 5:
                        color = glm::vec3(1.0f, 0.5f, 0.0f);
                        break;
                }
                bricks.push_back(Brick(pos,size,color,SpriteManager::getSprite("block")));
            } //else no se agrega un ladrillo en esa posicion
        }
    }

    //Iniciar jugador
    player = Player(SpriteManager::getSprite("paddle"));

    //Iniciar pelota
    glm::vec2 ballPosition = player.getPosition()+glm::vec2(player.getSize().x/2.0f - 12.5f,-25.0f);
    ball = Ball(ballPosition,glm::vec2(100.0f,-350.0f),&player,SpriteManager::getSprite("ball"));
}