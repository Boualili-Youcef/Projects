#pragma once

#include <iostream>
#include "../Position.hpp"

class Building
{
private:
    std::string name; 
    int health;
    Position position;

public:
    Building(const std::string& name,int health, const Position& position);

    // Getter pour la vitesse de collecte et la capacité de transport
    int getHealth() const;
    std::string getName() const;
    Position getPosition() const;
};
