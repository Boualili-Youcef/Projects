#include "../../include/network/CityConnection.hpp"

CityConnection::CityConnection(const std::shared_ptr<BaseCity> &city1, const std::shared_ptr<BaseCity> &city2, ConnectionType type, double traffic, double distance, double spreadFactor)
    : city1(city1), city2(city2), type(type), traffic(traffic), distance(distance), spreadFactor(spreadFactor) {};

    double CityConnection::calculateSpreadRisk() const 
    {
        const double BASE_TRAFFIC_IMPACT = 0.6;  // Impact de base du trafic
        double risk = 0.0;
    
        switch(type) {
            case ConnectionType::AIR:
                // Pour l'avion : la distance a peu d'impact, le trafic est crucial
                risk = 0.8 + (0.2 * traffic);  // Base élevée + bonus trafic
                // Légère pénalité pour très longues distances (fatigue, escales...)
                if (distance > 5000) {
                    risk *= 0.9;
                }
                break;
    
            case ConnectionType::ROAD:
                // Pour la route : forte dépendance distance/trafic
                if (distance < 100) {
                    // Courtes distances : risque élevé, très influencé par le trafic
                    risk = 0.7 + (0.3 * pow(traffic, 1.5));
                } else if (distance < 500) {
                    // Moyennes distances : risque modéré
                    risk = 0.5 + (0.3 * traffic);
                    risk *= exp(-distance/1000.0);  // Décroissance avec la distance
                } else {
                    // Longues distances : risque faible (peu de gens font de très longs trajets)
                    risk = 0.2 * traffic;
                }
                break;
    
            case ConnectionType::SEA:
                // Pour la mer : distance peu importante, trafic modéré
                risk = 0.4 + (0.3 * traffic);
                // Bonus pour les routes maritimes principales
                break;
    
            default:  // RAIL ou autres
                risk = 0.5 + (0.2 * traffic);
                risk *= exp(-distance/800.0);
        }
    
        // Application du facteur de propagation avec limites
        risk = std::min(1.0, risk * spreadFactor);
        risk = std::max(0.001, risk);  // Risque minimum de base
    
        return risk;
    }