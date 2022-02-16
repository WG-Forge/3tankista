#include "game.h"

#include "game_configuration.h"

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
    while (this->window != nullptr)
    {
        this->ProcessWindowEvent();
        if (this->window == nullptr)
        {
            return;
        }

        ecs::ecsEngine->Update(DELTA_TIME_STEP);

        this->UpdateStateMachine();
    }
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

    glfwSetWindowCloseCallback(
        this->window,
        [](GLFWwindow* window)
        { ecs::ecsEngine->SendEvent<WindowCloseEvent>(); });
    glfwSetFramebufferSizeCallback(
        this->window,
        [](GLFWwindow* window, int width, int height)
        { ecs::ecsEngine->SendEvent<WindowResizedEvent>(width, height); });
}

void Game::Terminate()
{

    this->UnregisterAllEventCallbacks();

    ecs::Terminate();

    if (this->window)
    {
        glfwDestroyWindow(this->window);
    }

    glfwTerminate();

    // this will break the main game loop.
    this->window = nullptr;
}

void Game::ProcessWindowEvent()
{
    glfwPollEvents();
}

void Game::GLFWWindowCloseCallback(const WindowCloseEvent* event)
{
    this->Terminate();
}

void Game::GLFWWindowCloseCallbackHelper(GLFWwindow* window)
{
    Game* app = (Game*)(glfwGetWindowUserPointer(window));
    app->Terminate();
}

void Game::RegisterEventCallbacks()
{
    this->RegisterEventCallback(&Game::GLFWWindowCloseCallback);
}

void Game::UnregisterEventCallbacks()
{
    this->UnregisterEventCallback(&Game::GLFWWindowCloseCallback);
}
