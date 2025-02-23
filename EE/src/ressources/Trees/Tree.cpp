#include "../include/ressources/Trees/Tree.hpp"

Tree::Tree(const std::string &name, int quantity, double time_to_gather, const Position &position, ResourceType type)
    : Ressource(name, quantity, time_to_gather, position, type) {}