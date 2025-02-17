#ifndef CITY_HPP
#define CITY_HPP

#include <iostream>

class BaseVirus
{
private:
    std::string name;
    double infection_rate;
    double mortality_rate;
    double incubation_periode;
    

public:
    BaseVirus(const std::string &name, double infection_rate, double mortality_rate);

    void display() const;

    std::string getName() const { return name; };
    ~BaseVirus() = default;
};

#endif // CITY_HPP