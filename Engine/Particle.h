#pragma once

#include <SFML/Graphics.hpp>


class Particle{
  
  public:
    Particle(float radius);
    ~Particle();

    void update(float deltatime);
    void render(sf::RenderWindow& window);

    // Accessors and Mutators
    void setPosition(float x, float y);
    void setVelocity(float x, float y);
    void setAcceleration(float x, float y);
    void setDragged(bool dragged);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;
    bool getDragged() const;
    float getRadius() const;
    float getMass() const;
    
  private:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    float radius;
    bool dragged;
    float mass;
    sf::CircleShape circle;
};
