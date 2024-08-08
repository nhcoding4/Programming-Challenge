#include "../headers/def.hpp"

// --------------------------------------------------------------------------------------------------------------------

void draw_particles(std::vector<Particle> *particles)
{
    for (auto &particle : *particles)
    {
        DrawCircle(
            std::round(particle.position.x),
            std::round(particle.position.y),
            particle.radius + 2,
            BLACK);

        DrawCircle(
            std::round(particle.position.x),
            std::round(particle.position.y),
            particle.radius,
            WHITE);

        DrawCircle(
            std::round(particle.position.x),
            std::round(particle.position.y),
            particle.radius,
            particle.color);

        DrawCircle(
            std::round(particle.position.x - particle.radius * 0.2),
            std::round(particle.position.y - particle.radius * 0.3),
            particle.radius * 0.6,
            WHITE);
    }
}

// --------------------------------------------------------------------------------------------------------------------

void create_particle(std::vector<Particle> *particles, Config *config)
{
    for (auto i = 0; i < config->total_particles; i++)
    {
        Particle new_particle{
            .radius{static_cast<float>(GetRandomValue(5, 25))},
            .position{
                .x{static_cast<float>(GetRandomValue(new_particle.radius, config->width - new_particle.radius))},
                .y{static_cast<float>(GetRandomValue(new_particle.radius, config->height - new_particle.radius))},
            },
            .movement{
                .x{static_cast<float>(GetRandomValue(0, 1) - static_cast<float>((rand()) / static_cast<float>((RAND_MAX))))},
                .y{static_cast<float>(GetRandomValue(0, 1) - static_cast<float>((rand()) / static_cast<float>((RAND_MAX))))},
            },
            .push{
                .x{0},
                .y{0},
            },
            .color{config->particle_color},
        };

        if (new_particle.radius <= 10)
        {
            new_particle.friction = 0.99;
        }
        else if (new_particle.radius <= 20)
        {
            new_particle.friction = 0.97;
        }
        else
        {
            new_particle.friction = 0.95;
        }

        particles->push_back(new_particle);
    }
}

// --------------------------------------------------------------------------------------------------------------------

void set_position(std::vector<Particle> *particles, Config *config)
{
    for (auto &particle : *particles)
    {
        particle.position = {
            .x{static_cast<float>(GetRandomValue(particle.radius, config->width - particle.radius))},
            .y{static_cast<float>(GetRandomValue(particle.radius, config->height - particle.radius))},
        };
    }
}

// --------------------------------------------------------------------------------------------------------------------

void update_particles(std::vector<Particle> *particles, Config *config)
{
    for (auto &particle : *particles)
    {
        particle.position.x += particle.movement.x + particle.push.x;
        particle.position.y += particle.movement.y + particle.push.y;

        particle.push.x *= particle.friction;
        particle.push.y *= particle.friction;

        if (particle.position.x - particle.radius < 0)
        {
            particle.position.x = particle.radius;
            particle.movement.x *= -1;
        }

        if (particle.position.x + particle.radius > static_cast<float>(config->width))
        {
            particle.position.x = static_cast<float>(config->width) - particle.radius;
            particle.movement.x *= -1;
        }

        if (particle.position.y - particle.radius < 0)
        {
            particle.position.y = particle.radius;
            particle.movement.y *= -1;
        }

        if (particle.position.y + particle.radius > static_cast<float>(config->height))
        {
            particle.position.y = static_cast<float>(config->height) - particle.radius;
            particle.movement.y *= -1;
        }

        particle.color.a = std::round(255.0 / (static_cast<float>(config->height) / particle.position.y));
    }
}

// --------------------------------------------------------------------------------------------------------------------
