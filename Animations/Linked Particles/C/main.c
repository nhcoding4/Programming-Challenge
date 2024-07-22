#include <raylib.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int width;
    int height;
    int fps;
    char *title;

} Config;

typedef struct
{
    int width;
    int height;
    int raidus;
    int x;
    int y;
    int movementX;
    int movementY;
} Particle;

Particle *createParticle();
void boundaries(Particle *particle);
void drawParticle(Particle *particle);
void moveParticle(Particle *particle);
void setMovement(Particle *particle);
void updateParticle(Particle *particle);

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
    boundaries(particle);
}

int main()
{
    Config *particles = (Config *)malloc(sizeof(Config) * 1);
    particles->height = 1000;
    particles->width = 1000;
    particles->fps = 60;
    particles->title = "Particles";

    InitWindow(particles->width, particles->height, particles->title);
    SetTargetFPS(particles->fps);

    Particle *particle = createParticle();
    particle->width = particles->width;
    particle->height = particles->height;
    particle->raidus = 30;
    particle->x = 50;
    particle->y = 50;

    setMovement(particle);

    while (!WindowShouldClose())
    {
        updateParticle(particle);
        BeginDrawing();
        ClearBackground(BLACK);
        drawParticle(particle);
        EndDrawing();
    }
    CloseWindow();
    free(particle);
}
