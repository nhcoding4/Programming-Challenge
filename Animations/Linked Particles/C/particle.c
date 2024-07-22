#include "def.h"

// --------------------------------------------------------------------------------------------------------------------

Particle makeParticle(int windowWidth, int windowHeight, double mouseRadius)
{
    Particle particle = {
        windowWidth : windowWidth,
        windowHeight : windowHeight,
        radius : GetRandomValue(5, 15),
        x : 0,
        y : 0,
        movementX : GetRandomValue(-2, 2),
        movementY : GetRandomValue(-2, 2),
        pushX : 0.0,
        pushY : 0.0,
        friction : 0.0,
        mouseRadius : mouseRadius,
    };

    setPosition(&particle);
    setFriction(&particle);

    return particle;
}

// --------------------------------------------------------------------------------------------------------------------

void boundaries(Particle *particle)
{
    if (particle->x - particle->radius < 0)
    {
        particle->x = particle->radius;
        particle->movementX *= -1;
    }
    if (particle->x + particle->radius > particle->windowWidth)
    {
        particle->x = particle->windowWidth - particle->radius;
        particle->movementX *= -1;
    }

    if (particle->y - particle->radius < 0)
    {
        particle->y = particle->radius;
        particle->movementY *= -1;
    }

    if (particle->y + particle->radius > particle->windowHeight)
    {
        particle->y = particle->windowHeight - particle->radius;
        particle->movementY *= -1;
    }
}

// --------------------------------------------------------------------------------------------------------------------

void drawParticle(Particle *particle)
{
    Color color = ColorFromHSV((float)particle->x, 1.0, 1.0);
    DrawCircle(particle->x, particle->y, (float)particle->radius, color);
}

// --------------------------------------------------------------------------------------------------------------------

void moveParticle(Particle *particle)
{
    particle->x += particle->movementX + round(particle->pushX);
    particle->y += particle->movementY + round(particle->pushY);
}

// --------------------------------------------------------------------------------------------------------------------

void pushParticle(Particle *particle, double mouseRadius)
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    double dx = (particle->x - mouseX);
    double dy = (particle->y - mouseY);

    double distance = hypot(dx, dy);

    if (distance < mouseRadius)
    {
        double power = (mouseRadius / distance) * 3;
        double angle = atan2(dy, dx);
        particle->pushX = cos(angle) * power;
        particle->pushY = sin(angle) * power;
    }
}

// --------------------------------------------------------------------------------------------------------------------

void setFriction(Particle *particle)
{
    if (particle->radius <= 7)
    {
        particle->friction = 0.99;
    }
    else if (particle->radius > 7 && particle->radius <= 10)
    {
        particle->friction = 0.97;
    }
    else
    {
        particle->friction = 0.95;
    }
}

// --------------------------------------------------------------------------------------------------------------------

void setPosition(Particle *particle)
{
    particle->x = GetRandomValue(0 + particle->radius, particle->windowWidth - particle->radius);
    particle->y = GetRandomValue(0 + particle->radius, particle->windowHeight - particle->radius);
}

// --------------------------------------------------------------------------------------------------------------------

void updateParticle(Particle *particle)
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        pushParticle(particle, particle->mouseRadius);
    }

    moveParticle(particle);
    boundaries(particle);
    updatePushPower(particle);
}

// --------------------------------------------------------------------------------------------------------------------

void updatePushPower(Particle *particle)
{
    particle->pushX *= particle->friction;
    particle->pushY *= particle->friction;
}

// --------------------------------------------------------------------------------------------------------------------

void updateScreenSizeParticle(Particle *particle, int newWidth, int newHeight)
{
    particle->windowWidth = newWidth;
    particle->windowHeight = newHeight;
    setPosition(particle);
}

// --------------------------------------------------------------------------------------------------------------------
