#include "../../include/city/BaseCity.hpp"

BaseCity::BaseCity(const std::string &name, int population)
    : name(name), population(population), infected(0), dead(0), recovered(0), infectionRate(0) {};

BaseCity::BaseCity(const std::string &name, int population, int infected, int dead, int recovered, double infectionRate)
    : name(name), population(population), infected(infected), dead(dead), recovered(recovered), infectionRate(infectionRate) {};

void BaseCity::display() const
{
    std::cout << "Stats: \n - Name: " << name << "\n - Population : " << population
              << " \n - infected : " << infected << "\n - Dead : " << dead << "\n - Recoverd : " << recovered << std::endl;
}