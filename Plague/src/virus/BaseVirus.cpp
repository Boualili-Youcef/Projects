#include "../../include/virus/BaseVirus.hpp"

BaseVirus::BaseVirus(const std::string &name, double infection_rate, double mortality_rate, double incubation_periode, double post_infection_immunity, double duration)
    : name(name), infection_rate(infection_rate), mortality_rate(mortality_rate), incubation_periode(incubation_periode), post_infection_immunity(post_infection_immunity), duration(duration) {};


void BaseVirus::display() const
{
    std::cout << "Virus caracteristics: \n - Name: " << name << "\n - Infection rate : " << infection_rate
              << " \n - Mortality rate : " << mortality_rate << "\n - Incubation periode : " << incubation_periode << "\n - Post infection immunity : " << post_infection_immunity << "\n - Duration : " << duration << std::endl;
}
