#pragma once

#include "Building.hpp"
#include "../ressources/Ressource.hpp"
#include "../Position.hpp"
#include <map>

class Depot : public Building
{
private:
    int capacity;
    std::map<ResourceType, int> resources;

public:
    Depot(const std::string &name, int health, const Position &position, int capacity);

    // Getter pour la capacité
    int getCapacity() const;
    int getResource(ResourceType type) const;

    // Setter pour la capacité
    void addResource(ResourceType type, int quantity);
};