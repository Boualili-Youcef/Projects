#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <thread>
#include "../include/npc/Citizen.hpp"
#include "../include/ressources/Trees/Olk.hpp"
#include "../include/buildings/Depot.hpp"
#include "../include/ressources/Ressource.hpp"

void moveAndGather(std::shared_ptr<Citizen> citizen, std::shared_ptr<Ressource> resource, sf::RectangleShape &citizenShape, Depot &depot)
{
    citizen->gatherResources(*resource, depot);
}

int main()
{
    cout << "Hello, World!" << endl;
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Citizen Gathering Resources");

    // Load the background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("map.jpg"))
    {
        std::cerr << "Error loading background image" << std::endl;
        return -1;
    }

    // Create a sprite for the background
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Create Citizens and an Olk resource
    std::vector<std::shared_ptr<Citizen>> citizens = {
        std::make_shared<Citizen>("Youcef", 50, 50, 100, 10, 5, 2, 50),
        std::make_shared<Citizen>("Rudolf", 50, 5, 100, 10, 5, 2, 50),
        std::make_shared<Citizen>("King", 600, 258, 100, 10, 5, 2, 50)};

    std::shared_ptr<Ressource> resource = std::make_shared<Ressource>("Wood", 500, 2.0, 300, 600, ResourceType::Wood);

    Depot depot("Main Depot", 1000, 100, 100, 10000); // Ajoutez les positions X et Y

    // Create shapes to represent the Citizens, the resource, and the depot
    std::vector<sf::RectangleShape> citizenShapes;
    for (const auto &citizen : citizens)
    {
        sf::RectangleShape shape(sf::Vector2f(20, 20));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(citizen->getPositionX(), citizen->getPositionY());
        citizenShapes.push_back(shape);
    }

    sf::CircleShape resourceShape(10);
    resourceShape.setFillColor(sf::Color::Green);
    resourceShape.setPosition(resource->getPositionX(), resource->getPositionY());

    sf::RectangleShape depotShape(sf::Vector2f(40, 40)); // Adjusted size to be more visible
    depotShape.setFillColor(sf::Color::Red);
    depotShape.setPosition(depot.getPositionX(), depot.getPositionY());

    // Create threads for each Citizen
    std::vector<std::thread> threads;
    for (size_t i = 0; i < citizens.size(); ++i)
    {
        threads.emplace_back(moveAndGather, citizens[i], resource, std::ref(citizenShapes[i]), std::ref(depot));
    }

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the background
        window.draw(backgroundSprite);

        // Draw the Citizens, the resource, and the depot
        for (size_t i = 0; i < citizens.size(); ++i)
        {
            citizenShapes[i].setPosition(citizens[i]->getPositionX(), citizens[i]->getPositionY());
            window.draw(citizenShapes[i]);
        }

        window.draw(resourceShape);
        window.draw(depotShape);

        // Display the contents of the window
        window.display();

        // Add a small delay to make the movement visible
        sf::sleep(sf::milliseconds(100));
    }

    // Join threads
    for (auto &thread : threads)
    {
        thread.join();
    }

    std::cout << "Gold: " << depot.getResource(ResourceType::Gold) << std::endl;
    std::cout << "Iron: " << depot.getResource(ResourceType::Iron) << std::endl;
    std::cout << "Food" << depot.getResource(ResourceType::Food) << std::endl;
    std::cout << "Wood: " << depot.getResource(ResourceType::Wood) << std::endl;

    return 0;
}