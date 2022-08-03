#include "Particle.h"
#include <iostream>


// Constructor
Particle::Particle(float radius) : dragged(false), 
  mass(radius * 20.f), circle(sf::CircleShape(radius)){
  this->radius = radius;
  circle.setOutlineThickness(3.f);
  circle.setOutlineColor(sf::Color::White);
  circle.setFillColor(sf::Color::Black);
  circle.setOrigin(radius, radius);
}

// Deconstructor
Particle::~Particle(){}

// Update particle's position 
void Particle::update(float deltatime){
  setAcceleration(-getVelocity().x * 0.8f * deltatime,
    -getVelocity().y * 0.8f * deltatime +1.5f);
  setVelocity(getVelocity().x + getAcceleration().x,
    getVelocity().y + getAcceleration().y);

  circle.move(getVelocity());
  //std::cout << "Velocity: " << getVelocity().x << "," << getVelocity().y << "\n";

  // Check Particle's position to window boundaries
  // X axis boundaries
  if(getPosition().x < getRadius()){
    setPosition(getRadius(), getPosition().y);
    setVelocity(-getVelocity().x * 0.8f, getVelocity().y);
  } 
  else if(getPosition().x > 900 - getRadius()){
    setPosition(900 - getRadius(), getPosition().y);
    setVelocity(-getVelocity().x * 0.8f, getVelocity().y); 
  }
  // Y axis boundaries
  if(getPosition().y > 800 - getRadius()){
    setPosition(getPosition().x, 800 - getRadius());
    setVelocity(getVelocity().x, -getVelocity().y * 0.8f);
  }
  else if(getPosition().y < getRadius()){
    setPosition(getPosition().x, getRadius());
    setVelocity(getVelocity().x, -getVelocity().y * 0.8f);
  }
}

// Draw Particle onto window
void Particle::render(sf::RenderWindow& window){
  window.draw(circle);
}


// Mutators
void Particle::setPosition(float x, float y){
  circle.setPosition(sf::Vector2f(x, y));
}

void Particle::setVelocity(float x, float y){
  
  velocity = sf::Vector2f(x, y);
}

void Particle::setAcceleration(float x, float y){
  acceleration = sf::Vector2f(x, y);
}

void Particle::setDragged(bool dragged){
  this->dragged = dragged;
}


// Accessors
sf::Vector2f Particle::getPosition() const {
  return circle.getPosition();
}

sf::Vector2f Particle::getVelocity() const {
  return velocity;
}

sf::Vector2f Particle::getAcceleration() const {
  return acceleration;
}

bool Particle::getDragged() const {
  return dragged;
}

float Particle::getRadius() const {
  return radius;
}

float Particle::getMass() const {
  return mass;
}
