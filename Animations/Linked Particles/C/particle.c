#include "./def.h"

Particle *createParticle()
{
    Particle *particle = (Particle *)malloc(sizeof(Particle) * 1);
    particle->height = 0;
    particle->width = 0;
    particle->movementX = 0;
    particle->movementY = 0;
    particle->x = 0;
    particle->y = 0;

    return particle;
}

void boundaries(Particle *particle)
{
    if (particle->x - particle->raidus < 0)
    {
        particle->x = particle->raidus;
        particle->movementX *= -1;
    }
    if (particle->x + particle->raidus > particle->width)
    {
        particle->x = particle->width - particle->raidus;
        particle->movementX *= -1;
    }

    if (particle->y - particle->raidus < 0)
    {
        particle->y = particle->raidus;
        particle->movementY *= -1;
    }

    if (particle->y + particle->raidus > particle->height)
    {
        particle->y = particle->height - particle->raidus;
        particle->movementY *= -1;
    }
}

void drawParticle(Particle *particle)
{
    Color color = ColorFromHSV((float)particle->x, 1.0, 1.0);
    DrawCircle(particle->x, particle->y, (float)particle->raidus, color);
}

void moveParticle(Particle *particle)
{
    particle->x += particle->movementX;
    particle->y += particle->movementY;
}

void setMovement(Particle *particle)
{
    srand(time(0));
    particle->movementX = (rand() % 4) - 2;
    particle->movementY = (rand() % 4) - 2;
}

void updateParticle(Particle *particle)
{
    moveParticle(particle);
    bounds(particle);
}