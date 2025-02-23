#include <iostream>
#include <algorithm>
#include "../include/game/Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Unit Movement"),
      citizen("Bob", Position{100, 100}, 100, 10, 100, Position{2, 10}, Position{0, 0}, false, 3, 10),
      depot("Depot", 1000, Position{700, 300}, 500)
{
    resources.push_back(std::make_shared<Pine>("Pine1", 50, 5.0, Position{450, 300}, ResourceType::Wood));
    resources.push_back(std::make_shared<Pine>("Pine2", 50, 5.0, Position{400, 350}, ResourceType::Wood));
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            std::cout << "Clic : (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
            citizen.move({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
        }
    }
}

void Game::update()
{
    float deltaTime = clock.restart().asSeconds();

    // Let the citizen choose the closest resource to the depot
    citizen.chooseClosestResourceToDepot(resources, depot);

    // Update the citizen's state for all resources
    for (auto &resource : resources)
    {
        citizen.update(deltaTime, *resource, depot);
    }

    removeEmptyResources();
}

void Game::removeEmptyResources()
{
    resources.erase(std::remove_if(resources.begin(), resources.end(),
                                   [](const std::shared_ptr<Ressource> &resource)
                                   {
                                       return resource->getQuantity() <= 0;
                                   }),
                    resources.end());
}

void Game::render()
{
    window.clear();

    for (const auto &resource : resources)
    {
        if (resource->getQuantity() > 0)
        {
            sf::ConvexShape pineShape;
            pineShape.setPointCount(3);
            pineShape.setPoint(0, sf::Vector2f(0, 0));
            pineShape.setPoint(1, sf::Vector2f(20, 40));
            pineShape.setPoint(2, sf::Vector2f(40, 0));
            pineShape.setFillColor(sf::Color::Green);
            pineShape.setPosition(resource->getPosition().x, resource->getPosition().y);
            window.draw(pineShape);
        }
    }

    sf::CircleShape citizenShape(10);
    citizenShape.setFillColor(sf::Color::Blue);
    citizenShape.setPosition(citizen.getPosition().x, citizen.getPosition().y);
    window.draw(citizenShape);

    sf::RectangleShape depotShape(sf::Vector2f(40, 40));
    depotShape.setFillColor(sf::Color(128, 128, 128));
    depotShape.setPosition(depot.getPosition().x, depot.getPosition().y);
    window.draw(depotShape);

    window.display();
}
