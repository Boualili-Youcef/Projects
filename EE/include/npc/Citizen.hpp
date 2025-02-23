#pragma once

#include <iostream>
#include "Unit.hpp"
#include "../ressources/Ressource.hpp"
#include "../buildings/Depot.hpp"

class Ressource; // Forward declaration
class Depot;     // Forward declaration

class Citizen : public Unit {
private:
    int gatheringSpeed;
    int carryingCapacity;
    int collectedRessources;
    ResourceType carriedResourceType;
    bool movingToDepot;
    bool movingToResource;
    float resourceX, resourceY;
    float depotX, depotY;

public:
    Citizen(std::string name, float positionX, float positionY, int health, int attack, int speed, int gatheringSpeed, int carryingCapacity);

    void gatherResources(Ressource &ressource, Depot &depot);
    void takeResourcesToDepot(Depot &depot);
    void setTargetPosition(float x, float y);
    // New method to move gradually toward a resource.
    void moveTowards(Ressource &ressource);

    int getGatheringSpeed() const;
    int getCarryingCapacity() const;
    int getCollectedRessources() const;
};