#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

// ----------------------------------------------------------------------------------------------------------------

// Data needed for drawing and updating on screen 'particles'.

typedef struct
{
    int32_t x, y, radius, movementX, movementY;
    double friction, pushX, pushY;
} Particle;

// ----------------------------------------------------------------------------------------------------------------

int main()
{
    // Window Properties
    int32_t windowWidth = 1000;
    int32_t windowHeight = 1000;
    int32_t targetFps = 144;
    char *title = "Particles rewrite";

    // Particle properties (note if totalParticles are changed then change array size below (Particles particles[x]).)
    int32_t totalParticles = 1000;
    int32_t connectionDistance = 100;
    int32_t lowerMovementBound = -3;
    int32_t upperMovementBound = 3;

    // Mouse properties
    int32_t mouseRadius = 250;
    int32_t mouseX = 0;
    int32_t mouseY = 0;
    bool mouseDown = false;

    // Connection properties
    double lineThickness = 2.5;
    double pushPower = 2.0;

    // Fps counter properties.
    char fpsValue[5] = {};
    int32_t fps = 0;

    // ----------------------------------------------------------------------------------------------------------------

    // Window Setup.

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, title);
    SetTargetFPS(targetFps);

    // ----------------------------------------------------------------------------------------------------------------

    // Make Particles.

    Particle particles[1000] = {};
    for (int32_t i = 0; i < totalParticles; i++)
    {
        Particle newParticle = {
            radius : GetRandomValue(5, 15),
            x : GetRandomValue(newParticle.radius, windowWidth - newParticle.radius),
            y : GetRandomValue(newParticle.radius, windowHeight - newParticle.radius),
            movementX : GetRandomValue(lowerMovementBound, upperMovementBound),
            movementY : GetRandomValue(lowerMovementBound, upperMovementBound),
        };

        if (newParticle.radius <= 7)
        {
            newParticle.friction = 0.99;
        }
        else if (newParticle.radius <= 11)
        {
            newParticle.friction = 0.95;
        }
        else
        {
            newParticle.friction = 0.90;
        }

        particles[i] = newParticle;
    }

    // ----------------------------------------------------------------------------------------------------------------

    // Mainloop.

    while (!WindowShouldClose())
    {
        // ------------------------------------------------------------------------------------------------------------

        // Updates.

        // ------------------------------------------------------------------------------------------------------------

        // Window Resizing.

        if (IsWindowResized())
        {
            windowWidth = GetScreenWidth();
            windowHeight = GetScreenHeight();
            for (int32_t i = 0; i < totalParticles; i++)
            {
                particles[i].x = GetRandomValue(particles[i].radius, windowWidth - particles[i].radius);
                particles[i].y = GetRandomValue(particles[i].radius, windowHeight - particles[i].radius);
                particles[i].movementX = GetRandomValue(lowerMovementBound, upperMovementBound);
                particles[i].movementY = GetRandomValue(lowerMovementBound, upperMovementBound);
            }
        }

        // ------------------------------------------------------------------------------------------------------------

        // Update FPS counter.

        fps = GetFPS();
        sprintf(fpsValue, "%d", fps);

        // ------------------------------------------------------------------------------------------------------------

        // Update Mouse status.

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            mouseDown = true;
            mouseX = GetMouseX();
            mouseY = GetMouseY();
        }
        else
        {
            mouseDown = false;
        }

        // ------------------------------------------------------------------------------------------------------------

        // Update Position.

        for (int32_t i = 0; i < totalParticles; i++)
        {
            if (mouseDown)
            {
                double dx = particles[i].x - mouseX;
                double dy = particles[i].y - mouseY;
                double distance = hypot(dx, dy);

                if (distance < mouseRadius)
                {
                    double power = (mouseRadius / distance) * pushPower;
                    double angle = atan2(dy, dx);
                    particles[i].pushX = cos(angle) * power;
                    particles[i].pushY = sin(angle) * power;
                }
            }

            particles[i].x += particles[i].movementX + round(particles[i].pushX);
            particles[i].y += particles[i].movementY + round(particles[i].pushY);

            if (particles[i].x < particles[i].radius)
            {
                particles[i].x = particles[i].radius;
                particles[i].movementX *= -1;
            }
            if (particles[i].x > windowWidth - particles[i].radius)
            {
                particles[i].x = windowWidth - particles[i].radius;
                particles[i].movementX *= -1;
            }
            if (particles[i].y < particles[i].radius)
            {
                particles[i].y = particles[i].radius;
                particles[i].movementY *= -1;
            }
            if (particles[i].y > windowHeight - particles[i].radius)
            {
                particles[i].y = windowHeight - particles[i].radius;
                particles[i].movementY *= -1;
            }

            particles[i].pushX *= particles[i].friction;
            particles[i].pushY *= particles[i].friction;
        }

        // ------------------------------------------------------------------------------------------------------------

        // Drawing

        // ------------------------------------------------------------------------------------------------------------

        BeginDrawing();
        ClearBackground(BLACK);

        // ------------------------------------------------------------------------------------------------------------

        // Draw Lines.

        for (int32_t i = 0; i < totalParticles; i++)
        {
            for (int32_t j = i; j < totalParticles; j++)
            {
                if (i == j)
                {
                    continue;
                }

                int32_t dx = particles[i].x - particles[j].x;
                int32_t dy = particles[i].y - particles[j].y;
                double distance = hypot(dx, dy);

                if (distance < connectionDistance)
                {
                    double opacity = 1 - (distance / connectionDistance);

                    Vector2 start = {particles[i].x, particles[i].y};
                    Vector2 end = {particles[j].x, particles[j].y};
                    Color color = {255, 255, 255, 255 * opacity}; // white + transparency.

                    DrawLineEx(start, end, lineThickness, color);
                }
            }
        }

        // ------------------------------------------------------------------------------------------------------------

        // Draw particles.

        for (int32_t i = 0; i < totalParticles; i++)
        {
            Color color = ColorFromHSV((float)particles[i].x, 1.0, 1.0);
            DrawCircle(particles[i].x, particles[i].y, particles[i].radius, color);
        }

        // ------------------------------------------------------------------------------------------------------------

        // Draw fps counter.

        DrawText(fpsValue, 0, 0, 40, GREEN);

        // ------------------------------------------------------------------------------------------------------------

        EndDrawing();

        // ------------------------------------------------------------------------------------------------------------
    }

    // Free Resources

    CloseWindow();

    // ----------------------------------------------------------------------------------------------------------------
}
