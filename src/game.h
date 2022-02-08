#pragma once

#include "game_events.h"
#include "game_types.h"
#include "simple_fsm.h"

#include "../third_party/ecs/src/ecs.h"

class Game : public ecs::event::IEventListener, public SimpleFSM
{
public:
    explicit Game(const std::string& title = "Game Name");
    ~Game() = default;

public:
    void Initialize();

    void Run();

public:
    //-------------------------------------------------------------------------------------------------
    // Summary:	Game State Transitions.
    //
    //				+-----------------+
    //				| NOT_INITIALIZED |
    //				+-----------------+
    //				         |
    //				         v
    //				  +-------------+
    //				  | INITIALIZED |
    //				  +-------------+
    //				         |
    //				         v
    //                +-------------+
    //				  |   LOGINED   |
    //				  +-------------+
    //				         |
    //				         v
    //				   +-----------+
    //			  +--->| RESTARTED |<-------------+
    //			  |    +-----------+              |
    //			  |          |                    |
    //			  |          v                    |
    //			  |     +---------+               |
    //			  |     | STARTED |-------------+ |
    //			  |     +---------+             | |
    //			  |          |   ^              v |
    //			  |          |   |         +--------+
    //			  |          |   +---------| PAUSED |
    //			  |          |   |         +--------+
    //			  |          v   v              ^ |
    //			  |     +---------+             | |
    //			  |     | RUNNING |-------------+ |
    //			  |     +---------+               |
    //			  |          |                    |
    //			  |          v                    |
    //			  |    +----------+               |
    //			  +----| GAMEOVER |<--------------+
    //			       +----------+               |
    //			             |                    |
    //			             v                    |
    //                +------------+              |
    //				  |  LOGOUTED  |<-------------+
    //				  +------------+
    //				         |
    //				         v
    //                +------------+
    //			      | TERMINATED |
    //			      +------------+
    //-------------------------------------------------------------------------------------------------

    // Define FSM Transition table
    BEGIN_TRANSITION_TABLE

    // Initial State
    TRANSITION_ENTRY(NULL_STATE,
                     Game::GS_INITIALIZED,
                     Game::GS_INITIALIZED_ENTER,
                     NO_ONLEAVE_PROC,
                     GameState::INITIALIZED)

    // Transition to 'LOGIN'
    TRANSITION_ENTRY(Game::GS_INITIALIZED,
                     Game::GS_LOGINED,
                     Game::GS_LOGINED_ENTER,
                     Game::GS_LOGINED_LEAVE,
                     GameState::LOGINED)

    END_TRANSITION_TABLE

    // 'INITIALIZED' gamestate
    void GS_INITIALIZED();
    void GS_INITIALIZED_ENTER();

    // 'LOGINED' gamestate
    void GS_LOGINED();
    void GS_LOGINED_ENTER();
    void GS_LOGINED_LEAVE();

    void OnLoginGame(const GameLoginEvent* event);

public:
    inline GameState GetActiveGameState() const
    {
        return (GameState)this->GetActiveState();
    }
    inline bool IsInitialized() const
    {
        return (this->GetActiveState() > GameState::INITIALIZED);
    }
    inline bool IsLogined() const
    {
        return (this->GetActiveState() == GameState::LOGINED);
    }

private:
    void InitializeECS();

private:
    const std::string gameTitle;
};
