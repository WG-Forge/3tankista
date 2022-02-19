#pragma once
#include "ecs.h"

class TurnComponent : public ecs::Component<TurnComponent>
{
public:
    explicit TurnComponent(const int numOfTurns, const int currentTurn, const int playersNumber)
        : numOfTurns(numOfTurns)
        , currentTurn(currentTurn)
        , playersNumber(playersNumber)
    {
    }
    ~TurnComponent() override = default;

public:
    void SetNumOfTurns(const int numOfTurns) { this->numOfTurns = numOfTurns; }
    auto GetNumOfTurns() const { return this->numOfTurns; }

    void SetCurrentTurn(const int currentTurn) { this->currentTurn = currentTurn; }
    auto GetCurrentTurn() const { return this->currentTurn; }

    bool isFinished() const { return currentTurn == numOfTurns; }

    void SetPlayersNumber(const int playersNumber) { this->playersNumber = playersNumber; }
    auto GetPlayersNumber() const { return this->playersNumber; }

private:
    int playersNumber;
    int numOfTurns;
    int currentTurn;
};