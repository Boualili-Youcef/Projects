#include <iostream>
#include "../include/city/BaseCity.hpp"
#include "../include/virus/BaseVirus.hpp"
#include "../include/network/CityConnection.hpp"

int main()
{
    BaseCity city("Calais", 35000);
    BaseVirus virus("Covid-19", 0.5, 0.1, 14, 0.1, 21);


    // Test de cityConnection
    std::shared_ptr<BaseCity> city1 = std::make_shared<BaseCity>("Calais", 35000);
    std::shared_ptr<BaseCity> city2 = std::make_shared<BaseCity>("Dunkerque", 90000);

     // Afficher les statistiques des deux villes
     city1->display();
     city2->display();
    CityConnection connection(city1, city2, ConnectionType::SEA, 0.5, 600, 0.7);

    // Infecter la première ville avec quelques cas
    city1->setInfected(3500);

    // Essayer de propager le virus
    bool transmitted = connection.propagateVirus(std::make_shared<BaseVirus>(virus));
    if (transmitted)
    {
        std::cout << "Le virus s'est propagé !" << std::endl;
    }
    else
    {
        std::cout << "Le virus ne s'est pas propagé." << std::endl;
    }

   

    return 0;
}