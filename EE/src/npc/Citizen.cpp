#include <iostream>
#include <string>
#include <thread>
#include <cmath>
#include "../include/npc/Citizen.hpp"

Citizen::Citizen(std::string name, int positionX, int positionY, int health, int attack, int speed, int gatheringSpeed, int carryingCapacity)
    : Unit(name, positionX, positionY, health, attack, speed),
      gatheringSpeed(gatheringSpeed),
      carryingCapacity(carryingCapacity),
      collectedRessources(0),
      movingToDepot(false),
      movingToResource(true)
{
}

void Citizen::gatherResources(Ressource &ressource, Depot &depot)
{
    resourceX = ressource.getPositionX();
    resourceY = ressource.getPositionY();
    depotX = depot.getPositionX();
    depotY = depot.getPositionY();
    carriedResourceType = ressource.getType();

    while (true)
    {
        if (movingToResource)
        {
            setTargetPosition(resourceX, resourceY);
            movingToResource = false;
        }

        if (getPositionX() == resourceX && getPositionY() == resourceY)
        {
            std::cout << getName() << " is gathering resources at speed " << gatheringSpeed
                      << " and has a carrying capacity of " << carryingCapacity << " units." << std::endl;
            while (ressource.getQuantity() > 0 && carryingCapacity > collectedRessources)
            {
                std::cout << getName() << " is waiting for " << gatheringSpeed << " seconds before gathering." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(gatheringSpeed));

                int toCollect = gatheringSpeed;
                if (ressource.getQuantity() < toCollect)
                {
                    toCollect = ressource.getQuantity();
                }

                ressource.setQuantity(ressource.getQuantity() - toCollect);
                collectedRessources += toCollect;

                std::cout << getName() << " has gathered " << toCollect << " units. Remaining resources: "
                          << ressource.getQuantity() << "." << std::endl;

                if (collectedRessources >= carryingCapacity)
                {
                    std::cout << getName() << " has reached carrying capacity." << std::endl;
                    movingToDepot = true;
                    break;
                }
            }
        }

        if (movingToDepot)
        {
            setTargetPosition(depotX, depotY);
            movingToDepot = false;
        }

        if (getPositionX() == depotX && getPositionY() == depotY)
        {
            takeResourcesToDepot(depot);
            movingToResource = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Citizen::moveTowards(Ressource &ressource)
{
    int targetX = ressource.getPositionX();
    int targetY = ressource.getPositionY();
    setTargetPosition(targetX, targetY);
}

void Citizen::takeResourcesToDepot(Depot &depot)
{
    std::cout << getName() << " is taking resources to the depot." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << getName() << " has deposited resources at the depot." << std::endl;
    depot.addResource(carriedResourceType, collectedRessources);
    collectedRessources = 0;
}

void Citizen::setTargetPosition(int x, int y)
{
    int deltaX = x - getPositionX();
    int deltaY = y - getPositionY();
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance < getSpeed())
    {
        setPosition(x, y);
    }
    else
    {
        double moveX = (deltaX / distance) * getSpeed();
        double moveY = (deltaY / distance) * getSpeed();
        setPosition(getPositionX() + static_cast<int>(moveX), getPositionY() + static_cast<int>(moveY));
    }

    std::cout << getName() << " is moving to (" << x << ", " << y << "). Current position: ("
              << getPositionX() << ", " << getPositionY() << ")." << std::endl;
}

int Citizen::getGatheringSpeed() const { return gatheringSpeed; }

int Citizen::getCarryingCapacity() const { return carryingCapacity; }

int Citizen::getCollectedRessources() const { return collectedRessources; }