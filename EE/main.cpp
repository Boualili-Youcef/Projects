#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/npc/Unit.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Unit Movement");

    // Position initiale au centre
    Unit unit("Soldier", 400, 300, 100, 10, 200); 

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // TODO: a supprimer !
                    std::cout << "Clic : (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
                    unit.move(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        // Temps écoulé depuis la dernière frame
        float deltaTime = clock.restart().asSeconds();

        // Mise à jour de l'unité
        unit.update(deltaTime);

        // Affichage
        window.clear();
        sf::CircleShape shape(10);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(unit.getPositionX(), unit.getPositionY());
        window.draw(shape);
        window.display();
    }

    return 0;
}
