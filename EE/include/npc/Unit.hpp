#pragma once

#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

class Unit
{
private:
    string name;              // Le nom de l'unité
    int positionX, positionY; // Position de l'unité sur une carte
    int health;               // Points de vie de l'unité
    int attack;               // Points d'attaque de l'unité
    int speed;                // Vitesse de déplacement

public:
    // Constructeur
    Unit(string name, int positionX, int positionY, int health, int attack, int speed);

    // Getters
    string getName() const;
    int getPositionX() const;
    int getPositionY() const;
    int getHealth() const;
    int getAttack() const;
    int getSpeed() const;

    // Méthode pour déplacer l'unité
    void move(int x, int y);
    void setPosition(int x, int y);
};
