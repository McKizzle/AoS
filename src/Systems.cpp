#include "Systems.hpp"

#include <iostream>

namespace aos 
{

Systems::Systems()
{
    std::cout << "Systems::Systems" << std::endl;
} 

Systems::~Systems()
{
    std::cout << "Systems::~Systems" << std::endl;
} 

int Systems::push_back(System * subsystem)
{
    std::cout << "Systems::push_back" << std::endl;
    this->children.push_back(subsystem);

    return 0;
}

void Systems::pop_back()
{
    std::cout << "Systems::pop_back" << std::endl;
    this->children.pop_back();
}


}
