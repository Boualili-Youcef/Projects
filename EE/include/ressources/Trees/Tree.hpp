#pragma once

#include "../Ressource.hpp"

#include "../../Position.hpp"

class Tree : public Ressource
{
public:
    Tree(const std::string &name, int quantity, double time_to_gather, const Position &Position, ResourceType type);
    ~Tree() = default;
};