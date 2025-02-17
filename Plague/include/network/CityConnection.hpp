#ifndef CITYCONNECTION_HPP
#define CITYCONNECTION_HPP

#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>

#include "../city/BaseCity.hpp"
#include "../virus/BaseVirus.hpp"

enum class ConnectionType
{
    ROAD,
    AIR,
    SEA
};

class CityConnection
{
private:
    std::shared_ptr<BaseCity> city1; // Pointeur vers la premiere ville
    std::shared_ptr<BaseCity> city2; // Pointeur vers la deuxieme ville
    ConnectionType type;             // Type de connexion
    double traffic;                  // Trafic sur la connexion (0.1 faible - 1 eleve)
    double distance;                 // Distance entre les deux villes (km)
    double spreadFactor;             // Facteur de propagation du virus sur cette connexion 

public:
    CityConnection(const std::shared_ptr<BaseCity> &city1, const std::shared_ptr<BaseCity> &city2, ConnectionType type, double traffic, double distance, double spreadFactor);

    // Methode pour calculer la probabilité de transmition d'un virus entre les deux villes
    double calculateSpreadRisk() const;

    // Methode pour propager un virus entre les deux villes
    bool propagateVirus(const std::shared_ptr<BaseVirus> &virus);

    ~CityConnection() = default;
};

#endif // CITYCONNECTION_HPP