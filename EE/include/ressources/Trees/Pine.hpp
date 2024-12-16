#pragma once

#include "Tree.hpp"

class Pine : public Tree
{
public:
    Pine(string name, int quantity, double time_to_gather, int positionX, int positionY, ResourceType type);
    
    ~Pine() = default;
};
