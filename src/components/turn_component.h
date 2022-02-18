#pragma once
#include "ecs.h"

class TurnComponent : public ecs::Component<TurnComponent>
{
public:
    explicit TurnComponent(const int numOfTurns, const int currentTurn)
        : numOfTurns(numOfTurns)
        , currentTurn(currentTurn)
    {
    }
    ~TurnComponent() override = default;

public:
    void SetNumOfTurns(const int numOfTurns) { this->numOfTurns = numOfTurns; }
    auto GetNumOfTurns() const { return this->numOfTurns; }

    void SetCurrentTurn(const int currentTurn) { this->currentTurn = currentTurn; }
    auto GetCurrentTurn() const { return this->currentTurn; }

    bool isFinished() const { return currentTurn == numOfTurns; }

private:
    int numOfTurns;
    int currentTurn;
};