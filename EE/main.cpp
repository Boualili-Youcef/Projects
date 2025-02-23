#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/npc/Unit.hpp"
#include "../include/ressources/Trees/Pine.hpp"
#include "../include/npc/Citizen.hpp"
#include "../include/buildings/Depot.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Unit Movement");

    // Instantiate Pine resource (adjust parameters as needed)
    Pine pine("Pine", 50, 3.0, {600, 300}, ResourceType::Wood);
    Citizen citizen("Bob", {100, 100}, 100, 10, 50, {2, 10}, {0, 0}, false, 2, 10);
    Depot depot("Depot", 1000, {700, 300}, 500);

    // Removed detached thread calling citizen.update()

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
                    std::cout << "Clic : (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
                    citizen.move({static_cast<float>(event.mouseButton.x),
                                  static_cast<float>(event.mouseButton.y)});
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        citizen.update(deltaTime, pine, depot); // update citizen movement

        window.clear();

        // Draw Pine as a green triangle
        sf::ConvexShape pineShape;
        pineShape.setPointCount(3);
        pineShape.setPoint(0, sf::Vector2f(0, 0));
        pineShape.setPoint(1, sf::Vector2f(20, 40));
        pineShape.setPoint(2, sf::Vector2f(40, 0));
        pineShape.setFillColor(sf::Color::Green);
        pineShape.setPosition(pine.getPosition().x, pine.getPosition().y);
        window.draw(pineShape);

        // Draw Citizen as a blue circle
        sf::CircleShape citizenShape(10);
        citizenShape.setFillColor(sf::Color::Blue);
        citizenShape.setPosition(citizen.getPosition().x, citizen.getPosition().y);
        window.draw(citizenShape);

        // Draw Depot as a gray rectangle (for example 40x40)
        sf::RectangleShape depotShape(sf::Vector2f(40, 40));
        depotShape.setFillColor(sf::Color(128, 128, 128));
        depotShape.setPosition(depot.getPosition().x, depot.getPosition().y);
        window.draw(depotShape);

        window.display();
    }

    return 0;
}
