#include "def.h"

int main()
{
    int windowWidth = 1000;
    int windowHeight = 1000;
    int targetFPS = 144;
    int totalParticles = 1000;
    int connectionDistance = 200;
    int mouseRadius = 250;
    double lineThickness = 2.5;
    double pushPower = 3.0;
    char *title = "Particles";

    Config simulation = makeConfig(windowWidth, windowHeight, targetFPS, totalParticles, title);
    initSimulation(&simulation);

    Effect effect = makeEffect(windowWidth, windowHeight, totalParticles, connectionDistance, mouseRadius, lineThickness, pushPower);

    while (!WindowShouldClose())
    {
        checkScreenSizeChange(&simulation, &effect);
        update(&effect);

        BeginDrawing();
        ClearBackground(BLACK);
        drawEffect(&effect);
        displayFPS();
        EndDrawing();
    }

    CloseWindow();
    freeEffect(&effect);
}
