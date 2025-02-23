#pragma once

#include "Tree.hpp"
#include "../../Position.hpp"

class Pine : public Tree
{
public:
    Pine(const std::string &name, int quantity, double time_to_gather, const Position &position, ResourceType type);

    ~Pine() = default;
};