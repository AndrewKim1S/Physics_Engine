#include "Engine.h"
#include <algorithm>

// Constructor
Engine::Engine(){
  draggedParticle = nullptr;
}

// Deconstructor
Engine::~Engine(){
  delete draggedParticle;
}

// Will Create Particles
void Engine::CreateParticle(size_t size, float x, float y) {
  Particle particle = Particle(size);
  particle.setPosition(x,y);
  particles.push_back(particle);
}

// Update particles check for collisions
void Engine::update(float deltatime){
  particleCollision();

  for(Particle& particle : particles){
    particle.update(deltatime);
  }
}

// Render the particles onto window
void Engine::render(sf::RenderWindow& window){
  for(Particle& particle : particles){
    particle.render(window);
  }
}

// Handles particle collisions
void Engine::particleCollision(){
  for(Particle& p1 : particles){
    for(Particle& p2 : particles){
      if(&p1 == &p2){
        continue;
      }
  //int counter = 0;
  //for(Particle p : particles){
    //for(size_t j = counter + 1; j < particles.size(); j++){
      //Particle p1 = particles[counter];
      //Particle p2 = particles[j];
      if(ParticleOverlap(p1, p2)){
        //std::cout << "if statement" << "\n";
        float distance = distanceSquared(p1.getPosition(), p2.getPosition());
        distance = sqrtf(distance);
        float overlap = (distance - p1.getRadius() - p2.getRadius())/ 2.f;
        // distance = std::fmax(distance, p1.getRadius() + p2.getRadius());

        // Move the particles so they do not intersect
        float moveX = (overlap * (p1.getPosition().x - p2.getPosition().x) / distance);
        float moveY = (overlap * (p1.getPosition().y - p2.getPosition().y) / distance);
        p1.setPosition(p1.getPosition().x - moveX, p1.getPosition().y - moveY);
        p2.setPosition(p2.getPosition().x + moveX, p2.getPosition().y + moveY);

        sf::Vector2f normal((p2.getPosition().x - p1.getPosition().x) / distance,
          (p2.getPosition().y - p1.getPosition().y) / distance);
        sf::Vector2f tangent(-normal.y, normal.x);

        float dotProductTan1 = p1.getVelocity().x * tangent.x + 
          p1.getVelocity().y * tangent.y;
        float dotProductTan2 = p2.getVelocity().x * tangent.x +
          p2.getVelocity().y * tangent.y;

        float dotProductNorm1 = p1.getVelocity().x * normal.x +
          p1.getVelocity().y * normal.y;
        float dotProductNorm2 = p2.getVelocity().x * normal.x + 
          p2.getVelocity().y * normal.y;

        float m1 = (dotProductNorm1 * (p1.getMass() - p2.getMass()) +
          2.0f * p1.getMass() * dotProductNorm2) / (p1.getMass() + p2.getMass());
        float m2 = (dotProductNorm2 * (p2.getMass() - p1.getMass()) +
          2.0f * p1.getMass() * dotProductNorm1) / (p1.getMass() + p2.getMass());

        float p1XV = std::fmin(std::fmax(tangent.x * dotProductTan1 + normal.x * m1 *0.8, -25.f), 25.f);
        float p1YV = std::fmin(std::fmax(tangent.y * dotProductTan1 + normal.y * m1 *0.8, -25.f), 25.f);
        float p2XV = std::fmin(std::fmax(tangent.x * dotProductTan2 + normal.x * m2 *0.8, -25.f), 25.f);
        float p2YV = std::fmin(std::fmax(tangent.y * dotProductTan2 + normal.y * m2 *0.8, -25.f), 25.f);

        /*if(abs(p1XV) < 0.1) { p1XV = 0.f; }
        if(abs(p1YV) < 0.1) { p1YV = 0.f; }
        if(abs(p2XV) < 0.1) { p2XV = 0.f; }
        if(abs(p2YV) < 0.1) { p2YV = 0.f; }
      */
        /*std::cout << "Collision" << std::endl;
        std::cout << "p1: " << p1XV << ", " << p1YV << "\n";
        std::cout << "Tan: " << tangent.x << ", " << tangent.y << "\n";
        std::cout << "Dot: " << dotProductTan1 << ", " << dotProductTan2 << "\n";
        std::cout << "Norm: " << normal.x << ", " << normal.y << "\n";
        std::cout << "m: " << m1 << "\n";
        */
        p1.setVelocity(p1XV, p1YV);
        p2.setVelocity(p2XV, p2YV);
      }
    }
    //counter ++;
  }
}

// Check whether mouse is dragging on a particle
bool Engine::dragParticle(sf::Vector2f point){
  for(Particle& particle : particles){
    if(ParticlePointOverlap(particle, point)){
      draggedParticle = &particle;
      return true;
    }
  }
  return false;
}

// Determine velocity of particle when dragging
void Engine::setDraggedVelocity(float x, float y){
  if(draggedParticle){

    float xV = (draggedParticle->getPosition().x - x) / 10;
    float yV = (draggedParticle->getPosition().y - y) / 10;

    draggedParticle->setVelocity(-xV, -yV);

    draggedParticle = nullptr;
  }
}

// Check if particles are colliding
bool Engine::ParticleOverlap(Particle p1, Particle p2) {
  float distSquare = distanceSquared(p1.getPosition(),
    p2.getPosition());
  float radiusSum = p1.getRadius() + p2.getRadius();
  return distSquare < (radiusSum * radiusSum);
}

// Check if point is within particle
bool Engine::ParticlePointOverlap(Particle p, sf::Vector2f point){
  float dist = distanceSquared(p.getPosition(), point);
  
  return dist < (p.getRadius() * p.getRadius());
}

// Find distance squared between two particles
float Engine::distanceSquared(sf::Vector2f a, sf::Vector2f b){
  float distX = a.x - b.x;
  float distY = a.y - b.y;
  return distX * distX + distY * distY;
}


// Accessors
Particle* Engine::getDraggedParticle() const{
  return draggedParticle;
}

std::vector<Particle> Engine::getParticles() const{
  return particles;
}
