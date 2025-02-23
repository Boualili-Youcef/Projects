#include <cmath>
#include "../include/npc/Unit.hpp"

Unit::Unit(std::string name, float positionX, float positionY, int health, int attack, int speed)
    : name(name), positionX(positionX), positionY(positionY), health(health), attack(attack), speed(speed), moving(false) {}

std::string Unit::getName() const { return name; }
float Unit::getPositionX() const { return positionX; }
float Unit::getPositionY() const { return positionY; }
int Unit::getHealth() const { return health; }
int Unit::getAttack() const { return attack; }
int Unit::getSpeed() const { return speed; }

void Unit::move(float targetX, float targetY)
{
    this->targetX = targetX;
    this->targetY = targetY;

    float deltaX = targetX - positionX;
    float deltaY = targetY - positionY;

    // Distance entre l'unité et la cible
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 0)
    {
        directionX = deltaX / distance;  // Normalisation
        directionY = deltaY / distance;
        moving = true;
    }
}

void Unit::update(float deltaTime)
{
    if (moving)
    {
        float moveX = directionX * speed * deltaTime;
        float moveY = directionY * speed * deltaTime;

        // Vérifier si l'unité atteint la cible
        if (std::abs(targetX - positionX) <= std::abs(moveX) &&
            std::abs(targetY - positionY) <= std::abs(moveY))
        {
            positionX = targetX;
            positionY = targetY;
            moving = false;
        }
        else
        {
            positionX += moveX;
            positionY += moveY;
        }
    }
}


