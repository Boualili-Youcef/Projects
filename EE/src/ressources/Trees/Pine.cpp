#include "../include/ressources/Trees/Pine.hpp"

Pine::Pine(const std::string &name, int quantity, double time_to_gather, const Position &position, ResourceType type)
    : Tree(name, quantity, time_to_gather, position, type) {}