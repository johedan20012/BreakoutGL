#include "Button.h"

#include "../../Physics/PhysicsFunctions.h"

Button::Button(std::string text,TextFont font,glm::vec2 pos)
    :text(text),font(font),state(ButtonState::NORMAL){
        clickArea = BoxCollider(pos,font.getTextDimensions(text,1.0f));
    }

void Button::center(float scrWidth,float scrHeight){
    glm::vec2 newPos;
    glm::vec2 size= clickArea.calculateDimensions();
    newPos.x = (scrWidth-size.x)/2.0f;
    newPos.y = (scrHeight-size.y)/2.0f;
    clickArea.moveTo(newPos);
}

void Button::update(){
    switch (state){
        case ButtonState::NORMAL:
            if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(Physics::PointInBox(glm::vec2(Mouse::getMouseX(),Mouse::getMouseY()),clickArea)){
                    state = ButtonState::CLICKED;
                }
            }
            break;
        
        case ButtonState::CLICKED:
            if(Mouse::buttonWentUp(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(Physics::PointInBox(glm::vec2(Mouse::getMouseX(),Mouse::getMouseY()),clickArea)){
                    state = ButtonState::RELEASED;
                }else{
                    state = ButtonState::NORMAL;
                }
            }
            break;

        case ButtonState::RELEASED:
            state = ButtonState::NORMAL;
            break;
    }
}

void Button::render(Shader& shader){
    switch (state){
        case ButtonState::NORMAL:
            font.renderText(text,clickArea.getMin(),1.0f,shader);
            break;
        
        case ButtonState::CLICKED:
            font.renderText(text,clickArea.getMin(),1.0f,shader,glm::vec4(0.0f,0.5f,0.0f,1.0f));
            break;

        case ButtonState::RELEASED:
            font.renderText(text,clickArea.getMin(),1.0f,shader);
            break;
    }
    //clickArea.render(ShaderManager::getShader("shader"));
}

bool Button::isActive(){
    return (state == ButtonState::RELEASED);
}