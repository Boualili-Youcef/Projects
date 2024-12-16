#include "../include/buildings/Depot.hpp"

Depot::Depot(string name, int health, int capacity, int positionX, int positionY) : Building(name, health, positionX, positionY), capacity(capacity)
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
        cout << "Quantity cannot be negative!" << endl;
    }
}

int Depot::getResource(ResourceType type) const
{
    return resources.at(type);
}
