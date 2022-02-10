#include "game/game.h"
#include "entities/obstacle.h"
int main(int argc, char** argv)
{
    Obstacle o1(GameObjectId);
    Game* gameInstance = new Game("Obstacle Demo");

    gameInstance->Initialize();

    gameInstance->Run();

    return 0;
}
