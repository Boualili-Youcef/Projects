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
      collectedRessources(0),
      gatheringCooldown(0.0f)
{
}

void Citizen::update(float deltaTime, Ressource &ressource, Depot &depot)
{
    if (gatheringCooldown > 0)
    {
        gatheringCooldown -= deltaTime;
        return;
    }

    // If carrying resources, prioritize going to the depot.
    if (collectedRessources >= carryingCapacity)
    {
        if (!isAtPosition(depot.getPosition()))
        {
            move(depot.getPosition());
            Unit::update(deltaTime);
            return;
        }
        else
        {
            handleDepot(ressource, depot);
            return;
        }
    }

    // Otherwise, if no resources, go towards the resource.
    if (shouldMoveToResource(ressource))
        return;

    Unit::update(deltaTime);

    if (!getMoving() && isAtPosition(ressource.getPosition()))
        handleGathering(ressource, depot);
}

// Vérifie si l'unité doit se déplacer vers une ressource
bool Citizen::shouldMoveToResource(Ressource &ressource)
{
    // Si l'unité n'est pas déjà en mouvement et qu'elle n'a pas de ressources, on vérifie si la ressource est disponible
    if (!getMoving() && collectedRessources == 0 && ressource.getQuantity() > 0)
    {
        // Si la ressource n'est pas à la position de l'unité, on se déplace
        if (!isAtPosition(ressource.getPosition()))
        {
            move(ressource.getPosition());
            return true; // On démarre le déplacement, inutile de continuer
        }
    }
    return false;
}

bool Citizen::isAtPosition(const Position &target)
{
    float epsilon = 0.01f;
    Position currPos = getPosition();
    return std::abs(currPos.x - target.x) < epsilon && std::abs(currPos.y - target.y) < epsilon;
}
void Citizen::handleGathering(Ressource &ressource, Depot &depot)
{
    if (ressource.getQuantity() > 0 && collectedRessources < carryingCapacity)
    {
        // Détermine combien la ressource peut être récoltée
        int gatherAmount = std::min(gatheringSpeed, ressource.getQuantity());

        // Ne pas dépasser la capacité de transport
        int availableSpace = carryingCapacity - collectedRessources;
        gatherAmount = std::min(gatherAmount, availableSpace);

        // Réduit la quantité de la ressource et ajoute à la quantité récoltée
        ressource.setQuantity(ressource.getQuantity() - gatherAmount);
        collectedRessources += gatherAmount;

        std::cout << getName() << " gathering: " << collectedRessources << "/" << carryingCapacity
                  << " - ressources restantes: " << ressource.getQuantity() << std::endl;

        // Set a cooldown period instead of sleeping.
        if (ressource.getQuantity() > 0 && collectedRessources < carryingCapacity)
        {
            gatheringCooldown = 0.5f * ressource.getTimeToGather();
        }
    }

    // Se déplacer vers le dépôt si la capacité est atteinte
    if (collectedRessources >= carryingCapacity)
    {
        move(depot.getPosition());
    }
}

void Citizen::handleDepot(Ressource &ressource, Depot &depot)
{
    depot.addResource(ressource.getType(), collectedRessources);
    std::cout << getName() << " dépose " << collectedRessources << " " << ressource.printTypeResource() << " au dépôt" << std::endl;
    std::cout << "Apres dépôt, le dépôt contient: " << depot.getResource(ressource.getType()) << " " << ressource.printTypeResource() << std::endl;

    collectedRessources = 0;
    currentResourceType = ResourceType::None; // Reset resource type after deposit

    // Vérifiez si la ressource est vide avant de se déplacer
    if (ressource.getQuantity() > 0)
    {
        move(ressource.getPosition()); // Retourne vers la ressource pour continuer la récolte
    }
}

void Citizen::chooseClosestResourceToDepot(const std::vector<std::shared_ptr<Ressource>> &resources, const Depot &depot)
{
    if (currentResourceType != ResourceType::None)
    {
        // Si le citoyen a déjà un type de ressource, il ne doit pas changer de ressource
        std::shared_ptr<Ressource> closestResource = nullptr;
        float minDistance = std::numeric_limits<float>::max();

        for (const auto &resource : resources)
        {
            // Si la ressource est du même type et a une quantité > 0
            if (resource->getType() == currentResourceType && resource->getQuantity() > 0)
            {
                // Calculer la distance de la ressource par rapport au citoyen
                float distance = sqrt(pow(resource->getPosition().x - depot.getPosition().x, 2) +
                                      pow(resource->getPosition().y - depot.getPosition().y, 2));
                // Si c'est la ressource la plus proche
                if (distance < minDistance)
                {
                    minDistance = distance;
                    closestResource = resource;
                }
            }
        }

        if (closestResource)
        {
            targetResource = closestResource;
            move(targetResource->getPosition()); // Déplace vers la ressource
        }
    }
    else
    {
        // Si aucune ressource n'a été choisie, alors choisir la plus proche parmi toutes les ressources
        float minDistance = std::numeric_limits<float>::max();
        std::shared_ptr<Ressource> bestResource = nullptr;

        for (const auto &resource : resources)
        {
            if (resource->getQuantity() > 0)
            {
                float distance = sqrt(pow(resource->getPosition().x - depot.getPosition().x, 2) +
                                      pow(resource->getPosition().y - depot.getPosition().y, 2));

                if (distance < minDistance)
                {
                    minDistance = distance;
                    bestResource = resource;
                }
            }
        }

        if (bestResource)
        {
            targetResource = bestResource;
            currentResourceType = targetResource->getType(); // Enregistre le type de ressource récolté
            move(targetResource->getPosition());             // Déplace vers la ressource
        }
    }
}

int Citizen::getGatheringSpeed() const { return gatheringSpeed; }

int Citizen::getCarryingCapacity() const { return carryingCapacity; }

int Citizen::getCollectedRessources() const { return collectedRessources; }