#include "game.h"

int main(int argc, char** argv)
{
    Game* gameInstance = new Game("Obstacle Demo");

    gameInstance->Initialize();

    gameInstance->Run();

    return 0;
}
