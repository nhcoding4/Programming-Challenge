#include "def.h"

// --------------------------------------------------------------------------------------------------------------------

void Init(Game *game)
{
    InitWindow(game->screenWidth, game->screenHeight, game->title);
    SetTargetFPS(game->fps);
}

// --------------------------------------------------------------------------------------------------------------------

void displayFPS()
{
    int currentFPS = GetFPS();
    char fpsStr[4];
    sprintf(fpsStr, "%d", currentFPS);

    DrawText(fpsStr, 0, 0, 40, GREEN);
}

// --------------------------------------------------------------------------------------------------------------------
