#include "PostProcessing.h"

#include <glad/glad.h>

#include <stdlib.h>

#include "ShaderManager.h"

unsigned int PostProcessing::framebuffer;

unsigned int PostProcessing::colorBuffers[2];
unsigned int PostProcessing::depthBuffer;

unsigned int PostProcessing::pingPongFramebuffers[2];

unsigned int PostProcessing::pingPongColorBuffers[2];

ArrayObject PostProcessing::QuadVAO;

Shader PostProcessing::blurShader;
Shader PostProcessing::bloomShader;

void PostProcessing::init(){
    //Generación del framebuffer que se usara para contener la escena antes de aplicarle el efecto de bloom
    glGenFramebuffers(1, &framebuffer);
    
    //Se generan los dos buffers de color
    glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++){
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, 800.0f, 600.0f, 0, GL_RGBA, GL_FLOAT, NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    } 

    //Generación del buffer de profundidad (renderBuffer)
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800.0f, 600.0f);

    //Unir buffers
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        // Se ligan los buffers de color y profundidad al framebuffer actual
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffers[0], 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, colorBuffers[1], 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

        // Se indica a openGl que dibuje en 2 buffers de color para este framebuffer
        unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, attachments);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "EL Framebuffer para el postprocessing no esta completo\n";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //Generación de los framebuffers de tipo "ping pong" y sus respectivos buffers de color
    glGenFramebuffers(2, pingPongFramebuffers);
    glGenTextures(2, pingPongColorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingPongFramebuffers[i]);
        glBindTexture(GL_TEXTURE_2D, pingPongColorBuffers[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, 800.0f, 600.0f, 0, GL_RGBA, GL_FLOAT, NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingPongColorBuffers[i], 0
        );
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float quadVertices[] = {
        // Posiciones       // Coordenadas de textura
        -1.0f,  1.0f, 0.0f,     0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
        1.0f,  1.0f, 0.0f,      1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 0.0f,
    };
    
    QuadVAO.generate();
    QuadVAO.bind();
        QuadVAO["VBO"] = BufferObject(GL_ARRAY_BUFFER);
        QuadVAO["VBO"].generate();
        QuadVAO["VBO"].bind();
        QuadVAO["VBO"].setData<GLfloat>(20,quadVertices,GL_STATIC_DRAW);
        QuadVAO["VBO"].setVertexAttribPointer<GLfloat>(0,3,GL_FLOAT,5,0);
        QuadVAO["VBO"].setVertexAttribPointer<GLfloat>(1,2,GL_FLOAT,5,3);
        QuadVAO["VBO"].unbind();
    QuadVAO.unbind();

    //==================== Shaders ===============================
    ShaderManager::loadShader("assets/shaders/PostProcessing.vs","assets/shaders/blur.fs","shaderBlur");
    ShaderManager::loadShader("assets/shaders/PostProcessing.vs","assets/shaders/bloom.fs","shaderBloom");

    blurShader = ShaderManager::getShader("shaderBlur");
    blurShader.activate();
    blurShader.setInt("image",0);

    bloomShader = ShaderManager::getShader("shaderBloom");
    bloomShader.activate();
    bloomShader.setInt("scene", 0);
    bloomShader.setInt("bloomBlur", 1);
}

void PostProcessing::bindFramebuffer(){
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void PostProcessing::renderFramebuffer(){
    bool horizontal = true, first_iteration = true;
    int amount = 5;
    blurShader.activate();
    for (unsigned int i = 0; i < amount; i++){
        glBindFramebuffer(GL_FRAMEBUFFER, pingPongFramebuffers[horizontal]); 
        blurShader.setInt("horizontal", horizontal);

        glBindTexture(
            GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingPongColorBuffers[!horizontal]
        ); 
        QuadVAO.bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
        QuadVAO.unbind();

        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    bloomShader.activate();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pingPongColorBuffers[!horizontal]);

    QuadVAO.bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
    QuadVAO.unbind();
}

void PostProcessing::cleanup(){
    glDeleteFramebuffers(1,&framebuffer);
    glDeleteTextures(2,colorBuffers);
    glDeleteRenderbuffers(1,&depthBuffer);

    glDeleteFramebuffers(2,pingPongFramebuffers);
    glDeleteTextures(2,pingPongColorBuffers);

    QuadVAO.cleanup();
}