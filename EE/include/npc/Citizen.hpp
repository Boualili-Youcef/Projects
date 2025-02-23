#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "Unit.hpp"
#include "../ressources/Ressource.hpp"
#include "../buildings/Depot.hpp"
#include "../Position.hpp"

class Ressource; // Forward declaration
class Depot;     // Forward declaration

class Citizen : public Unit
{
private:
    int gatheringSpeed;
    int carryingCapacity;
    int collectedRessources;
    std::shared_ptr<Ressource> targetResource;             // Ressource actuelle du citoyen
    ResourceType currentResourceType = ResourceType::None; // Type de ressource récolté actuellement
    float gatheringCooldown;
public:
    // Nouveau constructeur utilisant Position
    Citizen(const std::string &name, const Position &position, int health, int attack, int speed,
            const Position &target, const Position &direction, bool moving,
            int gatheringSpeed, int carryingCapacity);

    // Méthodes
    void update(float deltaTime, Ressource &ressource, Depot &depot);
    bool shouldMoveToResource(Ressource &ressource);
    bool isAtPosition(const Position &target);
    void handleGathering(Ressource &ressource, Depot &depot);
    void handleDepot(Ressource &ressource, Depot &depot);
    void chooseClosestResourceToDepot(const std::vector<std::shared_ptr<Ressource>> &resources, const Depot &depot);

    // Getters
    int getGatheringSpeed() const;
    int getCarryingCapacity() const;
    int getCollectedRessources() const;
};
