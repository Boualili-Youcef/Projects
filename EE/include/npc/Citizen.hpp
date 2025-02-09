#pragma once

#include "Unit.hpp"
#include "../ressources/Ressource.hpp"
#include "../buildings/Depot.hpp"

class Citizen : public Unit {
private:
    int gatheringSpeed;
    int carryingCapacity;
    int collectedRessources;
    ResourceType carriedResourceType;
    bool movingToDepot;
    bool movingToResource;
    int resourceX, resourceY;
    int depotX, depotY;

public:
    Citizen(std::string name, int positionX, int positionY, int health, int attack, int speed, int gatheringSpeed, int carryingCapacity);

    void gatherResources(Ressource &ressource, Depot &depot);
    void takeResourcesToDepot(Depot &depot);
    void setTargetPosition(int x, int y);

    int getGatheringSpeed() const;
    int getCarryingCapacity() const;
    int getCollectedRessources() const;
};