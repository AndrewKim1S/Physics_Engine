#include <iostream>
#include "Engine.h"
#include <ctime>


int main(){
  sf::RenderWindow window(sf::VideoMode(900, 800), "Physics_Engine");
  window.setPosition(sf::Vector2i(180,50));
  window.setFramerateLimit(60);

  srand(static_cast<unsigned>(time(0)));

  Engine engine;

  sf::Vertex line[] = {sf::Vertex(sf::Vector2f(-1,-1)),
    sf::Vertex(sf::Vector2f(-1,-1))};

  bool dragging = false;

  float deltatime = 0.f;
  sf::Clock clock;

  while(window.isOpen()){
    sf::Event event;

    deltatime = clock.restart().asSeconds();

    while(window.pollEvent(event)){
      switch(event.type){
        
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::MouseButtonPressed:
          {
          sf::Vector2i point = sf::Mouse::getPosition(window);
          if(event.mouseButton.button == sf::Mouse::Left){
            
            if(engine.dragParticle(sf::Vector2f(static_cast<float>(point.x),
              static_cast<float>(point.y)))){
              dragging = true;
            } 
          }
          else if(event.mouseButton.button == sf::Mouse::Right){
              engine.CreateParticle(rand() % 25 + 45,
                static_cast<float>(point.x),
                static_cast<float>(point.y));
          }
          break;
          }

        case sf::Event::MouseButtonReleased:
          if(event.mouseButton.button == sf::Mouse::Left){

            engine.setDraggedVelocity(line[1].position.x, 
              line[1].position.y);
            dragging = false;
          }
          break;

        default:
          break;
      }
    }

    if(dragging){
      sf::Vector2i point = sf::Mouse::getPosition(window);

      line[0] = sf::Vertex(sf::Vector2f(engine.getDraggedParticle()->getPosition()),
        sf::Color::White);
      line[1] = sf::Vertex(sf::Vector2f(static_cast<float>(point.x),
        static_cast<float>(point.y)), sf::Color::White);
    }

    engine.update(deltatime);

    window.clear(sf::Color::Black);
    engine.render(window);

    if(dragging){
      window.draw(line, 2, sf::Lines);
    }

    window.display();
  }

  return 0;
}
