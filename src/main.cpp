#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>  //Maneja las direcciones de las funciones de OpenGl, siempre incluir antes de GLFW
#include <GLFW/glfw3.h>  //Maneja la creación de ventana , i/0, etc.
#include <stb/stb_image.h> //Maneja el import de imagenes para texturas

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// Librerias para matematicas
/*#include "Math/Vector3D.hpp"
#include "Math/Matrix3D.hpp"
#include "Math/Matrix4D.hpp"*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// juego
#include "Game/Level.h"

// Graficos
#include "Graphics/SpriteManager.h"

// I/O
#include "IO/Keyboard.h"
#include "IO/Mouse.h"


void framebufferSizeCallback(GLFWwindow* window,int witdh, int height);

Level level;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(){
    //Inicializa la semilla de los números aleatorios con el tiempo actual
    srand (time(NULL));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(800,600, "Hola OpenGL", NULL, NULL);
    if(window == NULL){
        std::cout << "No se pudo crear la ventana GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "No se pudo iniciar GLAD\n";
        return -1;
    }

    glViewport(0,0,800, 600); //Pone el rango de dibujo para OpenGl, esto puede ser menor que el tamaño de la ventana de GLFW
    glEnable(GL_BLEND); //Activa y configura el alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Pone los callbacks necesarios
    glfwSetFramebufferSizeCallback(window,framebufferSizeCallback);
    glfwSetMouseButtonCallback(window,Mouse::mouseButtonCallback);
    glfwSetCursorPosCallback(window,Mouse::cursorPosCallback);
    glfwSetScrollCallback(window,Mouse::mouseWheelCallback);
    glfwSetKeyCallback(window,Keyboard::keyCallback);

    //Iniciamos el spriteRenderer
    SpriteRenderer::init();

    //================================MODELOS ================================


    // =================== SHADERS =============================
    Shader shader("assets/shaders/2DObject.vs","assets/shaders/2DObject.fs");
    //Shader* shader2 = new Shader("assets/shaders/object.vs","assets/shaders/object2.fs");

    //Poner los uniforms
    glm::mat4 projection = glm::ortho(0.0f,800.0f,600.0f,0.0f,-1.0f,1.0f);
    shader.activate();
    shader.setInt("image",0);
    shader.setFloatMat4("projection",projection);

    // =================== Texturas ==============================
    SpriteManager::loadSprite("assets/textures/block_solid.png","block_solid",false);
    SpriteManager::loadSprite("assets/textures/block.png","block",false);
    SpriteManager::loadSprite("assets/textures/background.jpg","background",false);
    SpriteManager::loadSprite("assets/textures/bar.png","bar",false);
    SpriteManager::loadSprite("assets/textures/barSticky.png","barSticky",false);
    SpriteManager::loadSprite("assets/textures/awesomeface.png","ball",false);
    SpriteManager::loadSprite("assets/textures/Power1.png","pow1",false);
    SpriteManager::loadSprite("assets/textures/Power2.png","pow2",false);
    SpriteManager::loadSprite("assets/textures/Power3.png","pow3",false);
    SpriteManager::loadSprite("assets/textures/Power4.png","pow4",false);
    SpriteManager::loadSprite("assets/textures/Power5.png","pow5",false);

    SpriteManager::loadSprite("assets/textures/debug/circleCollider.png","DEBUG_1",false);
    SpriteManager::loadSprite("assets/textures/debug/boxCollider.png","DEBUG_2",false);

    // ================== Objetos ================================
    level.load("assets/levels/test.txt",800,300);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe mode
    //Bucle de dibujo (render loop)
    while(!glfwWindowShouldClose(window)){ /*Corre mientras no se le diga a GLFW que debe cerrar */
        //Calcular el deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        //Entrada
        if(Keyboard::key(GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window,true);
        }

        //Update
        level.update(deltaTime);
     
        //Comando de render aqui
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Render
        SpriteRenderer::drawSprite(SpriteManager::getSprite("background"),shader,glm::vec2(0.0f,0.0f),glm::vec2(800.0f,600.0f),0,glm::vec3(1.0f));
        level.render(shader);
        
        
        // Checa eventos e intercambia los buffers
        glfwPollEvents(); //Checa eventos de mouse,teclado,joystick,etc. y llama a los callbacks necesarios
        glfwSwapBuffers(window); //Cambia el buffer de color y lo "pone" en la pantalla, esto es usar doble buffer
    }

    /* Limpieza general de todo */
    shader.cleanup();

    SpriteRenderer::cleanup();

    SpriteManager::cleanup();

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}