#include "../include/ressources/Ressource.hpp"

Ressource::Ressource(const std::string &name, int quantity, double time_to_gather, const Position &position, ResourceType type)
    : name(name), quantity(quantity), time_to_gather(time_to_gather), position(position), type(type)
{
}

const std::string &Ressource::getName() const
{
    return name;
}

int Ressource::getQuantity() const
{
    return quantity;
}

double Ressource::getTimeToGather() const
{
    return time_to_gather;
}

Position Ressource::getPosition() const
{
    return position;
}

ResourceType Ressource::getType() const
{
    return type;
}

void Ressource::setQuantity(int quantity)
{
    if (quantity >= 0)
    {
        this->quantity = quantity;
    }
    else
    {
        std::cout << "Quantity cannot be negative!" << std::endl;
    }
}

std::string Ressource::printTypeResource() const
{
    switch (type)
    {
    case ResourceType::Gold:
        return "Gold";
    case ResourceType::Iron:
        return "Iron";
    case ResourceType::Food:
        return "Food";
    case ResourceType::Wood:
        return "Wood";
    default:
        return "Unknown";
    }
}
