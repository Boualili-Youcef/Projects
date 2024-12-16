#include "../include/ressources/Trees/Tree.hpp"

Tree::Tree(string name, int quantity, double time_to_gather, int positionX, int positionY, ResourceType type)
    : Ressource(name, quantity, time_to_gather, positionX, positionY, type) {}