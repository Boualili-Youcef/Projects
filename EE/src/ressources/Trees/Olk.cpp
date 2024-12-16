#include "../include/ressources/Trees/Olk.hpp"

Olk::Olk(std::string name, int quantity, double time_to_gather, int positionX, int positionY, ResourceType type)
    : Tree(name, quantity, time_to_gather, positionX, positionY, type) {}