#include "entities/map/obstacle.h"
#include "game/game.h"

int main(int argc, char** argv)
{
    Game* gameInstance = new Game("WOT:Strategy");

    gameInstance->Initialize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, GAME_WINDOW_FULLSCREEN);

    gameInstance->Run();

    delete gameInstance;

    return 0;
}
