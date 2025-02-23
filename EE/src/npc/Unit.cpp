#include <cmath>
#include "../include/npc/Unit.hpp"

Unit::Unit(const std::string &name, const Position &position, int health, int attack, int speed, const Position &target, const Position &direction, bool moving)
    : name(name), position(position), health(health), attack(attack), speed(speed), target(target), direction(direction), moving(moving) {}

std::string Unit::getName() const { return name; }
Position Unit::getPosition() const { return {position.x, position.y}; }
int Unit::getHealth() const { return health; }
int Unit::getAttack() const { return attack; }
int Unit::getSpeed() const { return speed; }
bool Unit::getMoving() const { return moving; }

void Unit::move(const Position& target)
{
    this->target = target;

    float deltaX = target.x - position.x;
    float deltaY = target.y - position.y;

    // Distance entre l'unité et la cible
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 0)
    {
        direction.x = deltaX / distance; // Normalisation
        direction.y = deltaY / distance;
        moving = true;
    }
}

void Unit::update(float deltaTime)
{
    if (moving)
    {
        float distanceRemaining = std::sqrt(std::pow(target.x - position.x, 2) + std::pow(target.y - position.y, 2));
        float step = speed * deltaTime;
        // Clamp step so as not to overshoot
        if (step > distanceRemaining)
            step = distanceRemaining;
        
        position.x += direction.x * step;
        position.y += direction.y * step;

        // Stop moving if we've virtually reached the target
        if (distanceRemaining <= 0.001f)
            moving = false;
    }
}
