#include "Game.h"

#include "../Graphics/PostProcessing.h"

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

    window = glfwCreateWindow(screenWidth,screenHeight, "BreakoutGL", NULL, NULL);
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
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_BLEND);//Activa y configura el alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Pone los callbacks necesarios
    glfwSetFramebufferSizeCallback(window,framebufferSizeCallback);
    glfwSetMouseButtonCallback(window,Mouse::mouseButtonCallback);
    glfwSetCursorPosCallback(window,Mouse::cursorPosCallback);
    glfwSetScrollCallback(window,Mouse::mouseWheelCallback);
    glfwSetKeyCallback(window,Keyboard::keyCallback);

    glfwSwapInterval(1);

    //Iniciamos el spriteRenderer
    SpriteRenderer::init();

    // =================== Texturas ==============================
    SpriteManager::loadSprite("assets/textures/logoInicio.png","INICIO_nombre",false);
    SpriteManager::loadSprite("assets/textures/fondoFront.png","fondo");
    SpriteManager::loadSprite("assets/textures/sun.png","sun");
    SpriteManager::loadSprite("assets/textures/sunBright.png","sunBright");
    SpriteManager::loadSprite("assets/textures/block_solid.png","block_solid",false);
    SpriteManager::loadSprite("assets/textures/block.png","block",false);
    SpriteManager::loadSprite("assets/textures/fondoPausa.png","pauseBackground",false);
    SpriteManager::loadSprite("assets/textures/bar.png","bar",false);
    SpriteManager::loadSprite("assets/textures/barSticky.png","barSticky",false);
    SpriteManager::loadSprite("assets/textures/ball3.png","ball",false);
    SpriteManager::loadSprite("assets/textures/Power1.png","pow1",false);
    SpriteManager::loadSprite("assets/textures/Power2.png","pow2",false);
    SpriteManager::loadSprite("assets/textures/Power3.png","pow3",false);
    SpriteManager::loadSprite("assets/textures/Power4.png","pow4",false);
    SpriteManager::loadSprite("assets/textures/Power5.png","pow5",false);
    SpriteManager::loadSprite("assets/textures/Power6.png","pow6",false);
    SpriteManager::loadSprite("assets/textures/Power7.png","pow7",false);
    SpriteManager::loadSprite("assets/textures/Power8.png","pow8",false);
    SpriteManager::loadSprite("assets/textures/Power9.png","pow9",false);
    SpriteManager::loadSprite("assets/textures/Power10.png","pow10",false);
    SpriteManager::loadSprite("assets/textures/Power11.png","pow11",false);
    SpriteManager::loadSprite("assets/textures/Power12.png","pow12",false);
    SpriteManager::loadSprite("assets/textures/Power13.png","pow13",false);

    SpriteManager::loadSprite("assets/textures/particle.png","particle",false);
    SpriteManager::loadSprite("assets/textures/particleFire.png","fireParticle",false);
    SpriteManager::loadSprite("assets/textures/laser.png","laser",false);

    SpriteManager::loadSprite("assets/textures/debug/circleCollider.png","DEBUG_1",false);
    SpriteManager::loadSprite("assets/textures/debug/boxCollider.png","DEBUG_2",false);

    SpriteManager::loadSprite("assets/textures/grid.png","grid",false);
    SpriteManager::loadSprite("assets/textures/gridBright.png","gridBright",false);
     // =================== SHADERS =============================
    ShaderManager::loadShader("assets/shaders/2DObject.vs","assets/shaders/2DObject.fs","shader");
    ShaderManager::loadShader("assets/shaders/text.vs","assets/shaders/text.fs","textShader");
    ShaderManager::loadShader("assets/shaders/3DObject.vs","assets/shaders/3DObject.fs","shader3D");
    ShaderManager::loadShader("assets/shaders/Terrain.vs","assets/shaders/Terrain.fs","assets/shaders/Terrain.gs","shaderTerrain");

    //====================================== Fuentes =============================
    fuente.init();
    fuente.loadFont("assets/fonts/OCRAEXT.TTF",24);

    //====================================== Camara ===================================
    camera = Camera(glm::vec3(25.0f,1.0f,0.0f),90.0f,10.0f,45.0f);

    //====================================== PostProcessing ============================
    PostProcessing::init();

    //Poner los uniforms
    glm::mat4 projection = glm::ortho(0.0f,800.0f,600.0f,0.0f,-10.0f,10.0f);
    Shader& shader = ShaderManager::getShader("shader");
    shader.activate();
    shader.setInt("image",0);
    shader.setFloatMat4("projection",projection);

    Shader& textShader = ShaderManager::getShader("textShader");
    textShader.activate();
    textShader.setInt("textImage",0);
    textShader.setFloatMat4("projection",projection);

    Shader& shader3D = ShaderManager::getShader("shader3D");
    shader3D.activate();
    shader3D.setInt("image",0);
    shader3D.setInt("brightMap",1);
    shader3D.setFloatMat4("model",glm::mat4(1.0f));
    shader3D.setFloatMat4("view",camera.getViewMatriz());
    shader3D.setFloatMat4("projection",glm::perspective(glm::radians(camera.getFov()), 800.0f / 600.0f, 0.1f, 100.0f));

    Shader& shaderTerrain = ShaderManager::getShader("shaderTerrain");
    shaderTerrain.activate();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model,glm::vec3(50.0f,50.0f,50.0f));
    shaderTerrain.setInt("image",0);
    shaderTerrain.setInt("brightMap",1);
    shaderTerrain.setFloatMat4("model",model);
    shaderTerrain.setFloatMat4("view",camera.getViewMatriz());
    shaderTerrain.setFloatMat4("projection",glm::perspective(glm::radians(camera.getFov()), 800.0f / 600.0f, 0.1F, 100.0f));
    shaderTerrain.setFloat3("tileCount",glm::vec3(100.0f,100.0f,0.0f));
    shaderTerrain.setFloat("ambientStrength",1.0f);

    terrain.generate(100,100);

    screen = new StartScreen(fuente);
    screen->init();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe mode
    return 0;
}

void Game::run(){ 
    float lastX = Mouse::getMouseX(),lastY = Mouse::getMouseY(),frame = 1;

    bool cameraLock = true;
    while(!glfwWindowShouldClose(window)){ /*Corre mientras no se le diga a GLFW que debe cerrar */
        //Calcular el deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float sensitivity = 0.1f;
        if(!cameraLock){
            camera.setYaw(camera.getYaw()+(Mouse::getMouseX()-lastX)*sensitivity);
            camera.setPitch(camera.getPitch() + (lastY-Mouse::getMouseY())*sensitivity);
        }

        lastX = Mouse::getMouseX();
        lastY = Mouse::getMouseY();

        float cameraSpeed = 10.0f*deltaTime;

        glm::vec3 cameraPos = camera.getPosition();
        glm::vec3 cameraFront = camera.getFront();
        glm::vec3 cameraUp = camera.getUp();
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        camera.setPosition(cameraPos);

        glm::mat4 view = camera.getViewMatriz();

        if(Keyboard::keyWentDown(GLFW_KEY_H) == GLFW_PRESS){
            cameraLock = !cameraLock;
        }

        //Update
        screen->update(deltaTime);
        if(screen->getState() == ScreenState::FINISHED){
            switch(screen->getType()){
                case ScreenType::START_SCREEN:
                    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
                    delete screen;
                    screen = new PlayScreen(fuente,((StartScreen*)screen)->gameInfinite());
                    screen->init();
                    break;
                case ScreenType::PLAY_SCREEN:
                    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
                    glfwSetCursorPos(window,400.0f,250.0f);
                    delete screen;
                    screen = new StartScreen(fuente);
                    screen->init();
                    break;
            }
        }else if(screen->getState() == ScreenState::CLOSE_GAME){
            glfwSetWindowShouldClose(window,true);
        }else if(screen->getType() == ScreenType::PLAY_SCREEN){
            switch (((PlayScreen*)screen)->getMouseState()){
                case 1:
                    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
                    break;
                
                case 2:
                    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
                    glfwSetCursorPos(window,400.0f,300.0f);
                    break;
            }
        }
     
        //Render de todo el juego
        render();

        Keyboard::reset();
        Mouse::reset();
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

    terrain.cleanup();

    fuente.cleanup();

    PostProcessing::cleanup();

    PhysicsManager::cleanup();

    ShaderManager::cleanup();

    SpriteRenderer::cleanup();

    SpriteManager::cleanup();

    glfwTerminate();
}

void Game::render(){
    //Se limpia el buffer de profundidad
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    //El renderizado del terreno y la skybox sera en el buffer para el postProcessing
    PostProcessing::bindFramebuffer();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Shader& shader3D  = ShaderManager::getShader("shader3D");
        shader3D.activate();
        shader3D.setFloatMat4("view",glm::mat4(glm::mat3(camera.getViewMatriz())));
        glActiveTexture(GL_TEXTURE1);
        SpriteManager::getSprite("fondo").bind();
        SpriteRenderer::drawSprite3D(SpriteManager::getSprite("fondo"),shader3D,glm::vec3(-1.0f,-1.0f,1.0f),glm::vec3(2.0f,2.0f,0.0f));
        
        glActiveTexture(GL_TEXTURE1);
        SpriteManager::getSprite("sunBright").bind();
        SpriteRenderer::drawSprite3D(SpriteManager::getSprite("sun"),shader3D,glm::vec3(-0.25f,0.0f,0.8f),glm::vec3(0.5f,0.5f,0.0f));
        glEnable(GL_DEPTH_TEST);
            glActiveTexture(GL_TEXTURE0);
            SpriteManager::getSprite("grid").bind();
            glActiveTexture(GL_TEXTURE1);
            SpriteManager::getSprite("gridBright").bind();
            Shader& shaderTerrain = ShaderManager::getShader("shaderTerrain");
            shaderTerrain.activate();
            shaderTerrain.setFloatMat4("view",camera.getViewMatriz());
            shaderTerrain.setFloat("ambientStrength",1.1f);
            terrain.render(shaderTerrain);
            glActiveTexture(GL_TEXTURE0);

    //Ahora se renderiza el buffer con el efecto de post-procesado utilizado
    PostProcessing::renderFramebuffer();

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glDisable(GL_DEPTH_TEST);
    //Por ultimo se renderiza la escena en 2D
    screen->render();  
}

void Game::framebufferSizeCallback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
    screenHeight = height;
    screenWidth = width;
}