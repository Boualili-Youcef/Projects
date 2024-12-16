#include "../include/buildings/Building.hpp"

Building::Building(string name, int health, int positionX, int positionY)
    : name(name), health(health), positionX(positionX), positionY(positionY)
{
}

int Building::getHealth() const
{
    return health;
}

string Building::getName() const
{
    return name;
}


int Building::getPositionX() const
{
    return positionX;
}

int Building::getPositionY() const
{
    return positionY;
}