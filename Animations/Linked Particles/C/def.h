#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct
{
    int windowWidth;
    int windowHeight;
    int fps;
    int particles;
    char *title;

} Config;

typedef struct
{
    int windowWidth;
    int windowHeight;
    int radius;
    int x;
    int y;
    int movementX;
    int movementY;
    int totalParticles;
    double pushX;
    double pushY;
    double friction;
    double mouseRadius;
} Particle;

typedef struct
{
    int windowWidth;
    int windowHeight;
    int totalParticles;
    int connectionDistance;
    Particle *particles;
    double mouseRadius;
} Effect;

// Functions related to the config struct.
Config makeConfig(int windowWidth, int windowHeight, int fps, int particles, char *title);
void checkScreenSizeChange(Config *config, Effect *effect);
void initSimulation(Config *config);

// Functions related to the effect struct.
Effect makeEffect(int windowWidth, int windowHeight, int totalParticles, int connectionDistance, double mouseRadius);
void addParticles(Effect *effect);
void connectParticles(Effect *effect);
void drawEffect(Effect *effect);
void freeEffect(Effect *effect);
void update(Effect *effect);
void updateScreenSizeEffect(Effect *effect, int newWidth, int newHeight);

// Functions related to the particle struct.
Particle makeParticle(int windowWidth, int windowHeight, double mouseRadius);
void boundaries(Particle *particle);
void drawParticle(Particle *particle);
void moveParticle(Particle *particle);
void pushParticle(Particle *particle, double mouseRadius);
void setFriction(Particle *particle);
void setPosition(Particle *particle);
void updateParticle(Particle *particle);
void updatePushPower(Particle *particle);
void updateScreenSizeParticle(Particle *particle, int newWidth, int newHeight);