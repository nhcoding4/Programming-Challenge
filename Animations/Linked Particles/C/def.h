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