#ifndef BASEVIRUS_HPP
#define BASEVIRUS_HPP

#include <string>
#include <iostream>

class BaseVirus {
public:
    BaseVirus(const std::string &name, double infection_rate, double mortality_rate, double incubation_periode, double post_infection_immunity, double duration);

    void display() const;

private:
    std::string name;
    double infection_rate;
    double mortality_rate;
    double incubation_periode;
    double post_infection_immunity;
    double duration;
};

#endif // BASEVIRUS_HPP