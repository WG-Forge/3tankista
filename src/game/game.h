#pragma once

#include "game/fsm/simple_fsm.h"
#include "game_events.h"
#include "game_types.h"

#include "ecs.h"

class Game : public ecs::event::IEventListener, public SimpleFSM
{
public:
    explicit Game(std::string title = "Game Name");
    ~Game() = default;

public:
    void Initialize();

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

    // Transition to 'RUNNING'
    TRANSITION_ENTRY(
        Game::GS_STARTED, Game::GS_RUNNING, Game::GS_RUNNING_ENTER, Game::GS_STARTED_LEAVE, GameState::RUNNING)

    // Transition to 'GAMEOVER'
    TRANSITION_ENTRY(
        Game::GS_RUNNING, Game::GS_GAMEOVER, Game::GS_GAMEOVER_ENTER, Game::GS_RUNNING_LEAVE, GameState::GAMEOVER)

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
    void GS_GAMEOVER(){};
    void GS_GAMEOVER_ENTER(){};
    void GS_RUNNING_LEAVE(){};

    void OnLoginGame(const GameLoginEvent* event);

public:
    inline GameState GetActiveGameState() const { return (GameState)this->GetActiveState(); }
    inline bool      IsInitialized() const { return (this->GetActiveState() > GameState::INITIALIZED); }
    inline bool      IsRestarted() const { return (this->GetActiveState() == GameState::RESTARTED); }

private:
    void InitializeECS();

private:
    const std::string gameTitle;
};
