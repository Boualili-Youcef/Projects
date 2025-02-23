#pragma once

#include <iostream>
#include "../Position.hpp"

enum class ResourceType
{
    Gold,
    Iron,
    Food,
    Wood,
    None
};

class Ressource
{
private:
    std::string name;
    int quantity;
    double time_to_gather;
    Position position; // Position de la ressource sur une carte
    ResourceType type;

public:
    Ressource(const std::string &name, int quantity, double time_to_gather, const Position &position, ResourceType type);
    virtual ~Ressource() = default;

    const std::string &getName() const;
    int getQuantity() const;
    double getTimeToGather() const;
    Position getPosition() const;
    ResourceType getType() const;

    std::string printTypeResource() const;

    void setQuantity(int quantity);
};