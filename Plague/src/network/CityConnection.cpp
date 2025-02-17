#include "../../include/network/CityConnection.hpp"

CityConnection::CityConnection(const std::shared_ptr<BaseCity> &city1, const std::shared_ptr<BaseCity> &city2, ConnectionType type, double traffic, double distance, double spreadFactor)
    : city1(city1), city2(city2), type(type), traffic(traffic), distance(distance), spreadFactor(spreadFactor) {};

double CityConnection::calculateSpreadRisk() const
{
    double ratio1 = (city1 && city1->getPopulation() > 0) ? static_cast<double>(city1->getInfected()) / city1->getPopulation() : 0.0;
    double ratio2 = (city2 && city2->getPopulation() > 0) ? static_cast<double>(city2->getInfected()) / city2->getPopulation() : 0.0;
    double infectedRatio = std::max(ratio1, ratio2);
    if(infectedRatio <= 0.0)
        return 0.0;

    double typeMultiplier = 1.0;
    switch(type)
    {
        case ConnectionType::AIR:
            typeMultiplier = 1.2;
            break;
        case ConnectionType::ROAD:
            typeMultiplier = 1.0;
            break;
        case ConnectionType::SEA:
            typeMultiplier = 0.8;
            break;
    }

    double risk = typeMultiplier * spreadFactor * traffic * infectedRatio;

    if (type == ConnectionType::ROAD || type == ConnectionType::SEA)
    {
        double distanceFactor = std::max(0.1, 1.0 - (distance / 1000.0));
        risk *= distanceFactor;
    }
    std::cout << "Risk: " << risk << std::endl;
    return risk;
}

// Methode pour propager un virus entre les deux villes 
bool CityConnection::propagateVirus(const std::shared_ptr<BaseVirus> &virus)
{
    double risk = calculateSpreadRisk();
    if (risk >= virus->getInfectionRate())
    {
        if (city1->getInfected() > 0 && city2->getInfected() == 0)
        {
            city2->setInfected(1);
            return true;
        }
        else if (city2->getInfected() > 0 && city1->getInfected() == 0)
        {
            city1->setInfected(1);
            return true;
        }
    }
    return false;
}
