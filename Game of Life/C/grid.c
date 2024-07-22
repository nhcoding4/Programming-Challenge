#include "def.h"

const int offsets[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

// --------------------------------------------------------------------------------------------------------------------

Grid makeGridStruct(Game *game)
{
    int rows = game->screenHeight / game->cellSize;
    int columns = game->screenWidth / game->cellSize;

    Grid newGrid = {
        rows : rows,
        columns : columns,
        cellSize : game->cellSize,
        alive : WHITE,
    };

    newGrid.grid = newIntGrid(&newGrid);
    setStartingStatus(&newGrid);

    return newGrid;
}

// --------------------------------------------------------------------------------------------------------------------

int countLiveNeighbors(Grid *grid, int x, int y)
{
    int liveCount = 0;

    for (int i = 0; i < 8; i++)
    {
        int neighborRow = (y + offsets[i][1] + grid->rows) % grid->rows;
        int neighborColumn = (x + offsets[i][0] + grid->columns) % grid->columns;
        liveCount += grid->grid[neighborRow][neighborColumn];
    }

    return liveCount;
}

// --------------------------------------------------------------------------------------------------------------------

void drawGrid(Grid *grid)
{
    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->columns; j++)
        {
            Color drawColor = BLACK;
            if (grid->grid[i][j] == 1)
            {
                drawColor = WHITE;
            }

            DrawRectangle(j * grid->cellSize + 1, i * grid->cellSize + 1, grid->cellSize - 1, grid->cellSize - 1, drawColor);
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------

void freeGrid(Grid *grid)
{
    for (int i = 0; i < grid->rows; i++)
    {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

// --------------------------------------------------------------------------------------------------------------------

int **newIntGrid(Grid *grid)
{
    int **blankGrid = (int **)malloc(sizeof(int *) * grid->rows + 1);

    for (int i = 0; i < grid->rows; i++)
    {
        int *newRow = (int *)malloc(sizeof(int) * grid->columns + 1);

        for (int j = 0; j < grid->columns; j++)
        {
            newRow[j] = 0;
        }
        blankGrid[i] = newRow;
    }

    return blankGrid;
}

// --------------------------------------------------------------------------------------------------------------------

void setStartingStatus(Grid *grid)
{
    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->columns; j++)
        {
            int choice = GetRandomValue(0, 10);
            if (choice < 2)
            {
                grid->grid[i][j] = 1;
            }
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------

void updateStatus(Grid *grid)
{
    int **blankGrid = newIntGrid(grid);

    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->columns; j++)
        {
            int liveNeightbours = countLiveNeighbors(grid, j, i);
            if (liveNeightbours == 3)
            {
                blankGrid[i][j] = 1;
            }
            else if (liveNeightbours == 2)
            {
                blankGrid[i][j] = grid->grid[i][j];
            }
            else
            {
                continue;
            }
        }
    }

    freeGrid(grid);
    grid->grid = blankGrid;
}

// --------------------------------------------------------------------------------------------------------------------
