#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int screenWidth;
    int screenHeight;
    int fps;
    int cellSize;
    char *title;
    Color background;
} Game;

typedef struct
{
    int rows;
    int columns;
    int cellSize;
    int **grid;
    Color alive;
} Grid;

typedef struct
{
    int x;
    int y;
} Pair;

// Functions Related to the Game struct.
void Init(Game *game);
void displayFPS();

// Functions related to the Grid struct.
Grid makeGridStruct(Game *game);
void drawGrid(Grid *grid);
void freeGrid(Grid *grid);
int **newIntGrid(Grid *grid);
void setStartingStatus(Grid *grid);
void updateStatus(Grid *grid);
