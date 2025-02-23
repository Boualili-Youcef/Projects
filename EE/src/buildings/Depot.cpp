#include "../include/buildings/Depot.hpp"

Depot::Depot(const std::string &name, int health, const Position &position, int capacity) : Building(name, health, position), capacity(capacity)
{
    resources[ResourceType::Gold] = 0;
    resources[ResourceType::Iron] = 0;
    resources[ResourceType::Food] = 0;
    resources[ResourceType::Wood] = 0;
}

int Depot::getCapacity() const
{
    return capacity;
}

void Depot::addResource(ResourceType type, int quantity)
{
    if (quantity >= 0)
    {
        resources[type] += quantity;
    }
    else
    {
        std::cout << "Quantity cannot be negative!" << std::endl;
    }
}

int Depot::getResource(ResourceType type) const
{
    return resources.at(type);
}
