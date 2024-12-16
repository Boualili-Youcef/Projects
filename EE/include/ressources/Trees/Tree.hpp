#pragma once

#include "../Ressource.hpp"

class Tree : public Ressource
{
public:
    Tree(string name, int quantity, double time_to_gather, int positionX, int positionY, ResourceType  type) ;
    ~Tree() = default;
};