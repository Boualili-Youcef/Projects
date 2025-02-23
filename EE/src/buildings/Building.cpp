#include "../include/buildings/Building.hpp"

Building::Building(const std::string &name, int health, const Position &position)
    : name(name), health(health), position(position)
{
}

int Building::getHealth() const
{
    return health;
}

std::string Building::getName() const
{
    return name;
}

Position Building::getPosition() const
{
    return position;
}
