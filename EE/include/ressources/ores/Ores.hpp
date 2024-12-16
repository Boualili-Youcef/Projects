#pragma once

#include "Ressource.hpp"

class Ores : public Ressource
{
public:
    Ores(string name, int quantity, double time_to_gather);
    ~Ores() = default;
};