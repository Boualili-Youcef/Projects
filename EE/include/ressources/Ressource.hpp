#pragma once

#include <iostream>

using namespace std;

enum class ResourceType
{
    Gold,
    Iron,
    Food,
    Wood
};

class Ressource
{
private:
    string name;
    int quantity;
    double time_to_gather;
    int positionX, positionY; // Position de l'unité sur une carte
    ResourceType type;

public:
    Ressource(string name, int quantity, double time_to_gather, int positionX, int positionY, ResourceType type);
    virtual ~Ressource() = default;

    const string &getName() const;
    int getQuantity() const;
    double getTimeToGather() const;
    int getPositionX() const;
    int getPositionY() const;
    ResourceType getType() const;

    void setQuantity(int quantity);
};