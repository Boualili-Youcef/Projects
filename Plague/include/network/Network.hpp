#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <vector>
#include <memory>

#include "city/BaseCity.hpp"

class Network
{
private:
    // Utilisation de shared_ptr pour activer le polymorphisme
    std::vector<std::shared_ptr<BaseCity>> cities;

public:
    Network();
   
    ~Network() = default;
};

#endif // NETWORK_HPP