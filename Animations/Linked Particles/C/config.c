#include "def.h"

// --------------------------------------------------------------------------------------------------------------------

void checkScreenSizeChange(Config *config, Effect *effect)
{
    if (IsWindowResized())
    {
        int newWidth = GetScreenWidth();
        int newHeight = GetScreenHeight();

        config->windowWidth = newWidth;
        config->windowHeight = newHeight;

        effect->windowWidth = newWidth;
        effect->windowHeight = newHeight;

        updateScreenSizeEffect(effect, newWidth, newHeight);
    }
}

// --------------------------------------------------------------------------------------------------------------------

void initSimulation(Config *config)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config->windowWidth, config->windowHeight, config->title);
    SetTargetFPS(config->fps);
}

// --------------------------------------------------------------------------------------------------------------------

Config makeConfig(int windowWidth, int windowHeight, int fps, int particles, char *title)
{
    Config newConfig = {
        windowWidth : windowWidth,
        windowHeight : windowHeight,
        fps : fps,
        particles : particles,
        title : title,
    };

    return newConfig;
}

// --------------------------------------------------------------------------------------------------------------------
