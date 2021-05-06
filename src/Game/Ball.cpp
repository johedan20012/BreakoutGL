#include "Ball.h"

Player* Ball::player = nullptr;

Ball::Ball(glm::vec2 position,float velMagnitude,Texture2D& sprite)
    : GameObject(position,0,glm::vec2(12.0f,12.0f),glm::vec4(1.0f),INITIAL_BALL_VELOCITY_DIR,sprite)
    , PhysicsEntity(new CircleCollider(position,6.0f),EntityType::BALL,(unsigned int)(EntityType::BRICK) | (unsigned int)(EntityType::PLAYER))
    ,diffPosX(0.5f),velMagnitude(velMagnitude), stuck(true),dead(false),through(false),fire(false){
        id = PhysicsManager::registerEntity(this);
        //Inicia el generador de particulas
        ballParticles = ParticleGenerator(glm::vec2(10.0f,10.0f),250,SpriteManager::getSprite("particle"));
}

Ball::~Ball(){
    PhysicsManager::unregisterEntity(id);
}

void Ball::setStuck(bool stuck){
    this->stuck = stuck;
}

bool Ball::isStuck(){
    return stuck;
}

bool Ball::hasFire(){
    return fire;
}

void Ball::update(float deltaTime,unsigned int scrWidth,unsigned int scrHeight){
    if(dead) return;
    
    if(!stuck){ //Actualiza la pelota si no esta atorada
        position += velMagnitude * velocity * deltaTime;
        if(position.x+size.x > scrWidth){
            position.x = scrWidth-size.x;
            velocity.x *= -1;
        }else if(position.x < 0){
            position.x = 0.0f;
            velocity.x *= -1;
        }

        if(position.y < 0){
            position.y = 0;
            velocity.y *= -1;
        }
    }else{
        float posX = diffPosX*(player->getSize().x-size.x);
        position = player->getPosition()+glm::vec2(posX,-size.y);
    }

    if(position.y > 600.0f-size.y){
        dead = true;
    }

    ballParticles.update(*this,deltaTime);

    hitbox->moveTo(position);
}

void Ball::render(Shader& shader){
    GameObject::render(shader);
    ballParticles.render(shader);
}

void Ball::reset(float velMag){
    position = player->getPosition()+glm::vec2(player->getSize().x/2.0f - 12.5f,-25.0f);
    
    velocity = INITIAL_BALL_VELOCITY_DIR;
    velMagnitude = velMag;
    stuck = true;
    dead = false;
}

void Ball::hit(PhysicsEntity* otherEntity){
    if(otherEntity->getType() == EntityType::PLAYER){
        hitPlayer();
    }else{ //Golpeó un labrillo
        hitBrick(static_cast<BoxCollider*>(otherEntity->getHitbox()));
    }
}

void Ball::applyModifier(ModifierType modifier){
    switch (modifier) {
        case ModifierType::FAST_BALL:
            velMagnitude = MAX_BALL_VELOCITY;
            break;
        
        case ModifierType::SLOW_BALL:
            velMagnitude = 364.0f;
            break;
        
        case ModifierType::THROUGH_BALL:
            through = true;
            break;
        
        case ModifierType::FIRE_BALL:
            fire = true;
            break;
    }
    if(fire){
        ballParticles = ParticleGenerator(glm::vec2(10.0f,10.0f),250,SpriteManager::getSprite("fireParticle"));
    }
}

bool Ball::isDead(){
    return dead;
}

void Ball::hitBrick(BoxCollider* brickHitbox){
    if(through) return;
    
    glm::vec2 center = hitbox->calculateCenter();
    glm::vec2 centerOther = brickHitbox->calculateCenter();
    glm::vec2 halfDimOther = brickHitbox->calculateDimensions() / 2.0f;
    
    glm::vec2 difference = hitbox->calculateCenter() - brickHitbox->calculateCenter();
    glm::vec2 clamped = glm::clamp(difference, -halfDimOther,halfDimOther);
    glm::vec2 closest = centerOther + clamped;
    difference = closest - center;
    
    float radius = hitbox->calculateDimensions().x / 2.0f;

    glm::vec2 dirDiff = Physics::DirectionVector(difference);
    if (dirDiff.x == 1.0f || dirDiff.x == -1.0f) {
        velocity.x *= -1;

        float penetration = radius - std::abs(difference.x);
        if (dirDiff.x == -1.0f){
            position.x += penetration;
        }else{
            position.x -= penetration; 
        }
    }else{
        velocity.y *= -1;

        float penetration = radius - std::abs(difference.y);
        if (dirDiff.y == 1.0f){
            position.y -= penetration;
        }else{
            position.y += penetration;
        }
    }

    velMagnitude *= 1.01f;
    if(velMagnitude > MAX_BALL_VELOCITY){
        velMagnitude = MAX_BALL_VELOCITY;
    }

    hitbox->moveTo(position);
}

void Ball::hitPlayer(){
    if(stuck || dead) return;
    float diff = (position.x-player->getPosition().x) / (player->getSize().x-size.x);
    diff = glm::clamp(diff,0.0f,1.0f);// diff \in [-1,1]

    if(player->isSticky() && velocity.y > 0){ //Si el jugador es pegajoso y la pelota esta cayendo, entonces la pelota se pega
        diffPosX = (position.x-player->getPosition().x) / (player->getSize().x-size.x);

        stuck = true;
    }
    float angle = (diff*150.0f)+15.0f;
    glm::vec3 newVelocityDir = glm::rotate(glm::vec3(-1.0f,0.0f,0.0f),glm::radians(angle),glm::vec3(0.0f,0.0f,1.0f));

    velocity.x = newVelocityDir.x;
    velocity.y = newVelocityDir.y;
    velocity = glm::normalize(velocity);
}

// ====================== Metodos estaticos ===================
void Ball::setPlayer(Player* p){
    player = p;
}