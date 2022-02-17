#pragma once

#include "game/fsm/simple_fsm.h"
#include "game_events.h"
#include "game_types.h"

#include "ecs.h"

class Game : public ecs::event::IEventListener, public SimpleFSM
{
public:
    explicit Game(const std::string& title = "Game Name");
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

    END_TRANSITION_TABLE

    // 'INITIALIZED' gamestate
    void GS_INITIALIZED();
    void GS_INITIALIZED_ENTER();

    // 'RESTARTED' gamestate
    void GS_RESTARTED();
    void GS_RESTARTED_ENTER();
    void GS_INITIALIZED_LEAVE();

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
