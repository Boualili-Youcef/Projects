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
        float moveX = direction.x * speed * deltaTime;
        float moveY = direction.y * speed * deltaTime;

        // Vérifier si l'unité atteint la cible
        if (std::abs(target.x - position.x) <= std::abs(moveX) &&
            std::abs(target.y - position.y) <= std::abs(moveY))
        {
            position.x = target.x;
            position.y = target.y;
            moving = false;
        }
        else
        {
            position.x += moveX;
            position.y += moveY;
        }
    }
}