#include "entities/map/obstacle.h"
#include "game/game.h"

// todo for Vlad                                                                             Done
// TODO: 1) add matrix multiplication;                                                         +
//       2) add projection matrix in shaders to work in code only with pixels and hexes:       +
//          a) check ortho() in glm.                                                           +
//       3) rework Matrix::det and Matrix::getInversed();                                      -
//       4) add global variables from render in separate file;                                 +
//       5) rework HealthBar;                                                                  -
//       6) add repaires and catapults;                                                        -
//       7) rework ShapeBufferIndex;                                                           -
//       8) rework Shapes and ShapeGenerator;                                                  -
int main(int argc, char** argv)
{
    Game* gameInstance = new Game("Obstacle Demo");

    gameInstance->Initialize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, GAME_WINDOW_FULLSCREEN);

    gameInstance->Run();

    delete gameInstance;

    return 0;
}
