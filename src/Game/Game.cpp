#include "Game.h"

int Game::screenWidth = 800.0f;
int Game::screenHeight = 600.0f;

int Game::init(){
    //Inicializa la semilla de los números aleatorios con el tiempo actual
    srand (time(NULL));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(screenWidth,screenHeight, "Hola OpenGL", NULL, NULL);
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

    glViewport(0,0,screenWidth,screenHeight); //Pone el rango de dibujo para OpenGl, esto puede ser menor que el tamaño de la ventana de GLFW
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
    SpriteManager::loadSprite("assets/textures/particle.png","particle",false);

    SpriteManager::loadSprite("assets/textures/debug/circleCollider.png","DEBUG_1",false);
    SpriteManager::loadSprite("assets/textures/debug/boxCollider.png","DEBUG_2",false);

    screen = new PlayScreen();
    screen->init();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe mode
    return 0;
}

void Game::run(){ 
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
        screen->update(deltaTime);
        if(screen->finished()){
            std::cout <<"Juego terminado\n";
            glfwSetWindowShouldClose(window,true);
        }
     
        //Comando de render aqui
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Render
        screen->render();
        
        // Checa eventos e intercambia los buffers
        glfwPollEvents(); //Checa eventos de mouse,teclado,joystick,etc. y llama a los callbacks necesarios
        glfwSwapBuffers(window); //Cambia el buffer de color y lo "pone" en la pantalla, esto es usar doble buffer
    }
}

void Game::cleanup(){
    /* Limpieza general de todo */
    if(screen != nullptr){
        delete screen;
        screen = nullptr;
    }

    ShaderManager::cleanup();

    SpriteRenderer::cleanup();

    SpriteManager::cleanup();

    glfwTerminate();
}

void Game::framebufferSizeCallback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
    screenHeight = height;
    screenWidth = width;
}