#pragma once

#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include "../Position.hpp"


class Unit {
private:
    std::string name;  // Nom de l'unité
    Position position; // Position actuelle
    int health;        // Points de vie
    int attack;        // Points d'attaque
    int speed;         // Vitesse de déplacement
    Position target;   // Position de la cible
    Position direction;// Vecteur de direction normalisé
    bool moving;       // Indique si l'unité est en mouvement

public:
    // Constructeur
    Unit(const std::string &name, const Position &position, int health, int attack, int speed, const Position &target, const Position &direction, bool moving);

    // Getters
    std::string getName() const;
    Position getPosition() const;
    int getHealth() const;
    int getAttack() const;
    int getSpeed() const;
    bool getMoving() const;

    // Méthodes
    void move(const Position& target);
    void update(float deltaTime);
};
