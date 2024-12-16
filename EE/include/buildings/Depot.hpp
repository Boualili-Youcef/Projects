#pragma once

#include "Building.hpp"
#include "../ressources/Ressource.hpp"
#include <map>
class Depot : public Building
{
private:
    int capacity;
    map<ResourceType, int> resources;

public:
    Depot(string name, int health, int positionX, int positionY, int capacity);

    // Getter pour la vitesse de collecte et la capacité de transport
    int getCapacity() const;
    int getResource(ResourceType type) const;

    // Setter pour la capacité
    void addResource(ResourceType type, int quantity);
};
