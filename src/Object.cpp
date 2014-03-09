#include "Object.hpp"

using namespace aos;
Object::Object()
{
    velocity.push_back(0.0);
    velocity.push_back(0.0);
    acceleration.push_back(0.0);
    acceleration.push_back(0.0);
    jerk.push_back(0.0);
    jerk.push_back(0.0);

    std::cout << "Object Constructor" << std::endl;
}

Object::~Object()
{
    std::cout << "Object Destructor" << std::endl; 
}

void Object::render(Uint32 dt_ms, Uint32 time) 
{
    std::cout << "Rendered Object" << std::endl;
}

void Object::update(Uint32 dt_ms, Uint32 time) 
{
    std::cout << "Updated Object" << std::endl;
}



