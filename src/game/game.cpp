#include "game.h"

#include "game_configuration.h"
#include "systems/render_system.h"

Game::Game(const std::string& title)
    : gameTitle(title)
    , window(nullptr)
    , fullscreen(false)
    , windowPosX(-1)
    , windowPosY(-1)
    , windowWidth(-1)
    , windowHeight(-1)
{
}

Game::~Game()
{
    this->UnregisterEventCallbacks();
}

void Game::Initialize(const int width, const int height, const bool fullscreen)
{
    this->windowWidth  = width;
    this->windowHeight = height;
    this->fullscreen   = fullscreen;

    this->ChangeState(GameState::INITIALIZED);

    this->RegisterEventCallbacks();
}

void Game::Run()
{
    while (!glfwWindowShouldClose(this->window))
    {
        this->ProcessWindowEvent();
        if (this->window == nullptr)
        {
            return;
        }

        ecs::ecsEngine->Update(DELTA_TIME_STEP);

        this->UpdateStateMachine();
    }

    this->Terminate();
}

void Game::InitializeECS()
{
    ecs::Initialize();
}

void Game::OnLoginGame(const GameLoginEvent* event)
{
    this->PushState(GameState::RESTARTED);
}

void Game::InitializeGLFW()
{
    if (!glfwInit())
    {
        const char* description;
        int         code = glfwGetError(&description);
        LogFatal("Failed to initialize GLFW " + code + ", " + description);
        glfwTerminate();
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->windowWidth,
                                    this->windowHeight,
                                    this->gameTitle.c_str(),
                                    NULL,
                                    NULL);
    if (window == NULL)
    {
        const char* description;
        int         code = glfwGetError(&description);
        LogFatal("Failed to create GLFW window " + code + ", " + description);
        glfwTerminate();
        return;
    }

    glfwGetWindowPos(this->window, &this->windowPosX, &this->windowPosY);
    glfwGetWindowSize(this->window, &this->windowWidth, &this->windowHeight);

    glfwSetKeyCallback(window, &Game::KeyCallback);
    glfwSetFramebufferSizeCallback(
        this->window,
        [](GLFWwindow* window, int width, int height)
        { ecs::ecsEngine->SendEvent<WindowResizedEvent>(width, height); });
}

void Game::Terminate()
{

    this->UnregisterAllEventCallbacks();

    ecs::Terminate();

    this->window = nullptr;

    glfwTerminate();
}

void Game::ProcessWindowEvent()
{
    glfwPollEvents();
}

void Game::RegisterEventCallbacks() {}

void Game::UnregisterEventCallbacks() {}

void Game::KeyCallback(
    GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property
    // to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
