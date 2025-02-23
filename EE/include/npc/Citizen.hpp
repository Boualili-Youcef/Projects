#pragma once

#include <iostream>
#include "Unit.hpp"
#include "../ressources/Ressource.hpp"
#include "../buildings/Depot.hpp"
#include "../Position.hpp"

class Ressource; // Forward declaration
class Depot;     // Forward declaration

class Citizen : public Unit
{
private:
    int gatheringSpeed;
    int carryingCapacity;
    int collectedRessources;

public:
    // Nouveau constructeur utilisant Position
    Citizen(const std::string &name, const Position &position, int health, int attack, int speed,
            const Position &target, const Position &direction, bool moving,
            int gatheringSpeed, int carryingCapacity);

    void depositResources(Depot &depot, Ressource &ressource);
    void gatherResources(Ressource &ressource, Depot &depot);

    void update(float deltaTime, Ressource &ressource, Depot &depot);

    int getGatheringSpeed() const;
    int getCarryingCapacity() const;
    int getCollectedRessources() const;
};
