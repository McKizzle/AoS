#include "includes.hpp"
#include "Physics.hpp"

namespace aos {
    void PhysicsGine::overrided() 
    {
        std::cout << "Overriden Physics" << std::endl;
    }
     
    void PhysicsGine::integrate()
    {
        std::cout << "Ran the integrater" << std::endl;     
    }

    PhysicsGine::PhysicsGine() 
    {
        std::cout << "Initialized the PhysicsGine" << std::endl;
    }

    PhysicsGine::~PhysicsGine() {
        std::cout << "Destroyed the PhysicsGine" << std::endl;
    }
}

