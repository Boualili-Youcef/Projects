#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../npc/Citizen.hpp"
#include "../buildings/Depot.hpp"
#include "../ressources/Trees/Pine.hpp"


class Game
{
private:
    sf::RenderWindow window;
    std::vector<std::shared_ptr<Ressource>> resources;
    Citizen citizen;
    Depot depot;
    sf::Clock clock;

public:
    Game();
    void run();
    void handleEvents();
    void update();
    void render();
    void removeEmptyResources();
};

#endif // GAME_HPP
