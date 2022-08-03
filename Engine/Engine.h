#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cmath>
#include <math.h>
#include "Particle.h"


class Engine{

  public:
    Engine();
    ~Engine();
 
    void CreateParticle(size_t size, float x, float y);
    void update(float deltatime);
    void render(sf::RenderWindow& window);

    void particleCollision();

    bool dragParticle(sf::Vector2f point);
    void setDraggedVelocity(float x, float y);

    bool ParticleOverlap(Particle p1, Particle p2);
    bool ParticlePointOverlap(Particle p, sf::Vector2f point);
    float distanceSquared(sf::Vector2f a, sf::Vector2f b);

    Particle* getDraggedParticle() const;
    std::vector<Particle> getParticles() const;

  private:
    std::vector<Particle> particles;
    Particle* draggedParticle;

};
