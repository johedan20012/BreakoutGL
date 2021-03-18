#include "SpriteRenderer.h"

ArrayObject SpriteRenderer::VAO;

void SpriteRenderer::init(){
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    VAO.generate();
    VAO.bind();
        VAO["VBO"] = BufferObject(GL_ARRAY_BUFFER);
        VAO["VBO"].generate();
        VAO["VBO"].bind();
        VAO["VBO"].setData<float>(24,vertices,GL_STATIC_DRAW);
        VAO["VBO"].setVertexAttribPointer<float>(0,4,GL_FLOAT,4,0);
        VAO["VBO"].unbind();
    VAO.unbind();
}

void SpriteRenderer::drawSprite(Texture2D& texture,Shader& shader,glm::vec2 pos,glm::vec2 size, float rotate, glm::vec3 color){
    shader.activate();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos,0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); //Esto traslada el centro del objeto a la mitad del mismo, asi el objeto rota sobre su propio centro
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); //Devuelve todo a como estaba

    model = glm::scale(model, glm::vec3(size, 1.0f)); 

    shader.setFloatMat4("model",model);
    shader.setFloat3("spriteColor",color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    VAO.bind();
    glDrawArrays(GL_TRIANGLES,0,6);
    VAO.unbind();
}

void SpriteRenderer::cleanup(){
    VAO.cleanup();
}