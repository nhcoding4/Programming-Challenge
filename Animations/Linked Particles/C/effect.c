#include "def.h"

// --------------------------------------------------------------------------------------------------------------------

Effect makeEffect(int windowWidth, int windowHeight, int totalParticles, int connectionDistance, double mouseRadius,
                  double lineThickness, double pushPower)
{
    Effect effect = {
        windowHeight : windowHeight,
        windowWidth : windowWidth,
        totalParticles : totalParticles,
        connectionDistance : connectionDistance,
        particles : NULL,
        mouseRadius : mouseRadius,
        lineThickness : lineThickness,
        pushPower : pushPower,
    };

    addParticles(&effect);

    return effect;
}

// --------------------------------------------------------------------------------------------------------------------

void addParticles(Effect *effect)
{
    Particle *particleArray = (Particle *)malloc(sizeof(Particle) * effect->totalParticles + 1);

    for (int i = 0; i < effect->totalParticles; i++)
    {
        Particle newParticle = makeParticle(effect->windowWidth, effect->windowHeight);
        particleArray[i] = newParticle;
    }

    effect->particles = particleArray;
}

// --------------------------------------------------------------------------------------------------------------------

void connectParticles(Effect *effect)
{
    for (int i = 0; i < effect->totalParticles; i++)
    {
        for (int j = i; j < effect->totalParticles; j++)
        {
            if (i == j)
            {
                continue;
            }

            int dx = effect->particles[i].x - effect->particles[j].x;
            int dy = effect->particles[i].y - effect->particles[j].y;
            double distance = hypot(dx, dy);

            if (distance < effect->connectionDistance)
            {
                double opacity = 1 - (distance / effect->connectionDistance);

                Vector2 start = {effect->particles[i].x, effect->particles[i].y};
                Vector2 end = {effect->particles[j].x, effect->particles[j].y};
                Color color = {255, 255, 255, (int)255 * opacity};

                DrawLineEx(start, end, effect->lineThickness, color);
            }
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------

void drawEffect(Effect *effect)
{
    connectParticles(effect);

    for (int i = 0; i < effect->totalParticles; i++)
    {
        drawParticle(&effect->particles[i]);
    }
}

// --------------------------------------------------------------------------------------------------------------------

void freeEffect(Effect *effect)
{
    free(effect->particles);
}

// --------------------------------------------------------------------------------------------------------------------

void update(Effect *effect)
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        effect->mouseX = GetMouseX();
        effect->mouseY = GetMouseY();
    }

    for (int i = 0; i < effect->totalParticles; i++)
    {
        updateParticle(&effect->particles[i], effect);
    }
}

// --------------------------------------------------------------------------------------------------------------------

void updateScreenSizeEffect(Effect *effect, int newWidth, int newHeight)
{
    effect->windowWidth = newWidth;
    effect->windowHeight = newHeight;

    for (int i = 0; i < effect->totalParticles; i++)
    {
        updateScreenSizeParticle(&effect->particles[i], newWidth, newHeight);
    }
}

// --------------------------------------------------------------------------------------------------------------------
