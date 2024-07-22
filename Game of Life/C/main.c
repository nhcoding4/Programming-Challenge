#include "def.h"

int main()
{
    Game game = {
        screenWidth : 1920,
        screenHeight : 1080,
        fps : 144,
        cellSize : 3,
        title : "Game of Life: C",
        background : BLACK,
    };

    Init(&game);

    Grid grid = makeGridStruct(&game);

    while (!WindowShouldClose())
    {
        updateStatus(&grid);
        BeginDrawing();
        ClearBackground(game.background);
        drawGrid(&grid);
        displayFPS();
        EndDrawing();
    }

    CloseWindow();
    freeGrid(&grid);
}
