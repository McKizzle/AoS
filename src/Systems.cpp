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

unsigned int Systems::push_back(System * subsystem)
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

void Systems::render(Uint32 dt_ms, Uint32 time) 
{
    for(std::vector<System *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->render(dt_ms, time);
    }
}
void Systems::update(Uint32 dt_ms, Uint32 time) 
{  
    for(std::vector<System *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->update(dt_ms, time);
    }
}
void Systems::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time)
{
    for(std::vector<System *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->send_event(keyboardStates, dt, time);
    }
}
}
