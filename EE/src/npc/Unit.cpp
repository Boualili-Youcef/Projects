#include <thread>
#include <chrono>
#include <cmath>
#include "../include/npc/Unit.hpp"

Unit::Unit(string name, int positionX, int positionY, int health, int attack, int speed)
    : name(name), positionX(positionX), positionY(positionY), health(health), attack(attack), speed(speed) {}

string Unit::getName() const { return name; }

int Unit::getPositionX() const { return positionX; }

int Unit::getPositionY() const { return positionY; }

int Unit::getHealth() const { return health; }

int Unit::getAttack() const { return attack; }

int Unit::getSpeed() const { return speed; }

void Unit::move(int targetX, int targetY) {
    // Calculer la différence entre la position actuelle et la cible
    int deltaX = targetX - positionX;
    int deltaY = targetY - positionY;

    // Calculer la distance totale (en ligne droite)
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    // Nombre de pas nécessaires pour atteindre la cible
    int steps = static_cast<int>(distance / speed);

    for (int i = 0; i < steps; ++i) {
        // Normaliser les déplacements pour que l'unité se déplace à la vitesse spécifiée
        double moveX = (deltaX / distance) * speed;
        double moveY = (deltaY / distance) * speed;

        setPosition(positionX + static_cast<int>(moveX), positionY + static_cast<int>(moveY));

        // Attendre un peu avant de faire le prochain pas
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Mettre à jour la position finale
    setPosition(targetX, targetY);
}

void Unit::setPosition(int x, int y) {
    positionX = x;
    positionY = y;
}
