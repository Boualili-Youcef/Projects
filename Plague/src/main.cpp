#include <iostream>
#include "../include/city/BaseCity.hpp"
#include "../include/virus/BaseVirus.hpp"
#include "../include/network/CityConnection.hpp"

int main() {
    BaseCity city("Calais", 35000);
    BaseVirus virus("Covid-19", 0.5, 0.1, 14, 0.1, 21);
    city.display();
    virus.display();

    // Test de cityConnection
    std::shared_ptr<BaseCity> city1 = std::make_shared<BaseCity>("Calais", 35000);
    std::shared_ptr<BaseCity> city2 = std::make_shared<BaseCity>("Dunkerque", 90000);
    CityConnection connection(city1, city2, ConnectionType::ROAD, 0.7, 60, 0.6);
    double risk = connection.calculateSpreadRisk();
    std::cout << risk << std::endl;
    return 0;
}