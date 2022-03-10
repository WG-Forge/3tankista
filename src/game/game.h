#pragma once

#include "game/fsm/simple_fsm.h"
#include "game_configuration.h"
#include "game_events.h"
#include "game_types.h"

#include "render/utility/opengl.h"

#include "ecs.h"

class Game : public ecs::event::IEventListener, public SimpleFSM
{
public:
    DECLARE_LOGGER
    explicit Game(std::string title = "Game Name");
    ~Game();

public:
    void Initialize(const int width, const int height, const bool fullscreen = false);

    void Run();

public:
    /*------------------------------------------------------------------------
     * Summary:	Game State Transitions.
     *
     *				+-----------------+
     *				| NOT_INITIALIZED |
     *				+-----------------+
     *				         |
     *				         v
     *				  +-------------+
     *				  | INITIALIZED |
     *				  +-------------+
     *				         |
     *				         v
     *				   +-----------+
     *			  +--->| RESTARTED |<-------------+
     *			  |    +-----------+              |
     *			  |          |                    |
     *			  |          v                    |
     *			  |     +---------+               |
     *			  |     | STARTED |-------------+ |
     *			  |     +---------+             | |
     *			  |          |   ^              v |
     *			  |          |   |         +--------+
     *			  |          |   +---------| PAUSED |
     *			  |          |   |         +--------+
     *			  |          v   v              ^ |
     *			  |     +---------+             | |
     *			  |     | RUNNING |-------------+ |
     *			  |     +---------+               |
     *			  |          |                    |
     *			  |          v                    |
     *			  |    +----------+               |
     *			  +----| GAMEOVER |<--------------+
     *			       +----------+               |
     *			             |                    |
     *			             v                    |
     *                +------------+              |
     *			      | TERMINATED |<-------------+
     *			      +------------+
     *------------------------------------------------------------------------*/

    // Define FSM Transition table
    BEGIN_TRANSITION_TABLE

    // Initial State
    TRANSITION_ENTRY(
        NULL_STATE, Game::GS_INITIALIZED, Game::GS_INITIALIZED_ENTER, NO_ONLEAVE_PROC, GameState::INITIALIZED)

    // Transition to 'RESTARTED'
    TRANSITION_ENTRY(Game::GS_INITIALIZED,
                     Game::GS_RESTARTED,
                     Game::GS_RESTARTED_ENTER,
                     Game::GS_INITIALIZED_LEAVE,
                     GameState::RESTARTED)

    // Transition to 'STARTED'
    TRANSITION_ENTRY(
        Game::GS_RESTARTED, Game::GS_STARTED, Game::GS_STARTED_ENTER, Game::GS_RESTARTED_LEAVE, GameState::STARTED)

    // Transition to 'TERMINATED'
    TRANSITION_ENTRY(Game::GS_RESTARTED,
                     Game::GS_TERMINATED,
                     Game::GS_TERMINATED_ENTER,
                     Game::GS_RESTARTED_LEAVE,
                     GameState::TERMINATED)

    // Transition to 'RUNNING'
    TRANSITION_ENTRY(
        Game::GS_STARTED, Game::GS_RUNNING, Game::GS_RUNNING_ENTER, Game::GS_STARTED_LEAVE, GameState::RUNNING)

    // Transition to 'GAMEOVER'
    TRANSITION_ENTRY(
        Game::GS_RUNNING, Game::GS_GAMEOVER, Game::GS_GAMEOVER_ENTER, Game::GS_RUNNING_LEAVE, GameState::GAMEOVER)

    // Transitions to 'TERMINATED'
    TRANSITION_ENTRY(Game::GS_GAMEOVER,
                     Game::GS_TERMINATED,
                     Game::GS_TERMINATED_ENTER,
                     Game::GS_GAMEOVER_LEAVE,
                     GameState::TERMINATED)

    END_TRANSITION_TABLE

    // 'INITIALIZED' gamestate
    void GS_INITIALIZED();
    void GS_INITIALIZED_ENTER();

    // 'RESTARTED' gamestate
    void GS_RESTARTED();
    void GS_RESTARTED_ENTER();
    void GS_INITIALIZED_LEAVE();

    // 'STARTED' gamestate
    void GS_STARTED();
    void GS_STARTED_ENTER();
    void GS_RESTARTED_LEAVE();

    // 'RUNNING' gamestate
    void GS_RUNNING();
    void GS_RUNNING_ENTER();
    void GS_STARTED_LEAVE();

    // 'GAMEOVER' gamestate
    void GS_GAMEOVER();
    void GS_GAMEOVER_ENTER();
    void GS_RUNNING_LEAVE();

    // 'TERMINATED' gamestate
    void GS_TERMINATED();
    void GS_TERMINATED_ENTER();
    void GS_GAMEOVER_LEAVE();

    void OnLoginGame(const GameLoginEvent* event);
    void OnStartGame(const StartGameEvent* event);
    void OnBadRestart(const BadRestartEvent* event);
    void OnQuitGame(const QuitGameEvent* event);

public:
    inline GameState GetActiveGameState() const { return (GameState)this->GetActiveState(); }
    inline bool      IsInitialized() const { return (this->GetActiveState() > GameState::INITIALIZED); }
    inline bool      IsRestarted() const { return (this->GetActiveState() == GameState::RESTARTED); }

private:
    void InitializeECS();

    void InitializeGLFW();

    void ProcessWindowEvent();

    void RegisterEventCallbacks();

    void UnregisterEventCallbacks();

    void Terminate();

private:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

private:
    GLFWwindow* window;

    int windowPosX;
    int windowPosY;

    int windowWidth;
    int windowHeight;

    bool fullscreen;

    const std::string gameTitle;
};
