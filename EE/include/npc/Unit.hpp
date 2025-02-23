#pragma once

#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

class Unit
{
private:
    string name;                  // Le nom de l'unité
    float positionX, positionY;   // Position de l'unité sur une carte
    int health;                   // Points de vie de l'unité
    int attack;                   // Points d'attaque de l'unité
    int speed;                    // Vitesse de déplacement
    float targetX, targetY;       // Position de la cible
    float directionX, directionY; // vecteur normalisé
    bool moving;

public:
    // Constructeur
    Unit(string name, float positionX, float positionY, int health, int attack, int speed);

    // Getters
    string getName() const;
    float getPositionX() const;
    float getPositionY() const;
    int getHealth() const;
    int getAttack() const;
    int getSpeed() const;

    // Méthode pour déplacer l'unité
    void move(float x, float y);
    void update(float deltaTime);
};
