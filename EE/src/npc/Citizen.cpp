#include <iostream>
#include <string>
#include <thread>
#include <cmath>
#include <algorithm> // Pour std::min
#include <chrono>
#include <thread>
#include "../include/npc/Citizen.hpp"

Citizen::Citizen(const std::string &name, const Position &position, int health, int attack, int speed,
                 const Position &target, const Position &direction, bool moving,
                 int gatheringSpeed, int carryingCapacity)
    : Unit(name, position, health, attack, speed, target, direction, moving),
      gatheringSpeed(gatheringSpeed),
      carryingCapacity(carryingCapacity),
      collectedRessources(0)
{
}

void Citizen::update(float deltaTime, Ressource &ressource, Depot &depot)
{
    // Auto move vers la ressource si le citoyen est inactif et n'a rien récolté
    float epsilon = 0.01f;
    Position currPos = getPosition();
    Position resourcePos = ressource.getPosition();
    if (!getMoving() && collectedRessources == 0 && ressource.getQuantity() > 0)
    {
        if (std::abs(currPos.x - resourcePos.x) > epsilon || std::abs(currPos.y - resourcePos.y) > epsilon)
        {
            move(resourcePos);
            return; // Attendre le prochain update pour que le mouvement démarre
        }
    }
    
    Unit::update(deltaTime);
    
    // ...existing gathering/depot code...
    if(!getMoving())
    {
        // Arrivé à la ressource ?
        if (std::abs(currPos.x - resourcePos.x) < epsilon &&
            std::abs(currPos.y - resourcePos.y) < epsilon)
        {
            if (ressource.getQuantity() > 0 && collectedRessources < carryingCapacity)
            {
                int gatherAmount = std::min(gatheringSpeed, ressource.getQuantity());
                ressource.setQuantity(ressource.getQuantity() - gatherAmount);
                collectedRessources += gatherAmount;
                std::cout << getName() << " gathering: " << collectedRessources << "/" << carryingCapacity << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            if (collectedRessources == carryingCapacity || ressource.getQuantity() <= 0)
            {
                move(depot.getPosition());
            }
        }
        // Arrivé au depot ?
        else if (std::abs(currPos.x - depot.getPosition().x) < epsilon &&
                 std::abs(currPos.y - depot.getPosition().y) < epsilon)
        {
            depot.addResource(ressource.getType(), collectedRessources);
            collectedRessources = 0;
            move(resourcePos);
        }
    }
}
int Citizen::getGatheringSpeed() const { return gatheringSpeed; }

int Citizen::getCarryingCapacity() const { return carryingCapacity; }

int Citizen::getCollectedRessources() const { return collectedRessources; }