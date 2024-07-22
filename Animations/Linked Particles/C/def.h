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
} Particle;

typedef struct
{
    int windowWidth;
    int windowHeight;
    int totalParticles;
    int connectionDistance;
    Particle *particles;
    double mouseRadius;
    int mouseX;
    int mouseY;
    double lineThickness;
    double pushPower;
} Effect;

// Functions related to the config struct.
Config makeConfig(int windowWidth, int windowHeight, int fps, int particles, char *title);
void checkScreenSizeChange(Config *config, Effect *effect);
void displayFPS();
void initSimulation(Config *config);

// Functions related to the effect struct.
Effect makeEffect(int windowWidth, int windowHeight, int totalParticles, int connectionDistance,
                  double mouseRadius, double lineThickness, double pushPower);
void addParticles(Effect *effect);
void connectParticles(Effect *effect);
void drawEffect(Effect *effect);
void freeEffect(Effect *effect);
void update(Effect *effect);
void updateScreenSizeEffect(Effect *effect, int newWidth, int newHeight);

// Functions related to the particle struct.
Particle makeParticle(int windowWidth, int windowHeight);
void boundaries(Particle *particle);
void drawParticle(Particle *particle);
void moveParticle(Particle *particle);
void pushParticle(Particle *particle, Effect *effect);
void setFriction(Particle *particle);
void setPosition(Particle *particle);
void updateParticle(Particle *particle, Effect *effect);
void updatePushPower(Particle *particle);
void updateScreenSizeParticle(Particle *particle, int newWidth, int newHeight);