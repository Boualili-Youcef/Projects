#ifndef CITY_HPP
#define CITY_HPP

#include <iostream>

class BaseCity
{
private:
    std::string name;
    int population;
    int infected;
    int dead;
    int recovered;
    double infectionRate;

public:
    BaseCity(const std::string &name, int population);
    BaseCity(const std::string &name, int population, int infected, int dead, int recovered, double infectionRate);

    // mise a jour de l'infection
    void update();
    void display() const;

    std::string getName() const { return name; }
    int getInfected() const { return infected; }
    int getPopulation() const { return population; }

    void setInfected(int infected) { this->infected = infected; };
    ~BaseCity() = default;
};

#endif // CITY_HPP