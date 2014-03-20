#include "System.hpp"
#include "includes.hpp"

namespace aos
{


System::System()
{
    std::cout << "System constructor" << std::endl;

}

System::~System()
{
    std::cout << "System destructor" <<std::endl;
}

void System::render(Uint32 dt_ms, Uint32 time)
{

}

void System::update(Uint32 dt_ms, Uint32 time)
{

}

} // END namespace aos
