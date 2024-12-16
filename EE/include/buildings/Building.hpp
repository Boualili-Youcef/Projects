#pragma once

#include <iostream>

using namespace std;

class Building
{
private:
    string name; 
    int health;
    int positionX, positionY;

public:
    Building(string name,int health, int positionX, int positionY);

    // Getter pour la vitesse de collecte et la capacité de transport
    int getHealth() const;
    string getName() const;
    int getPositionX() const;
    int getPositionY() const;
};
