#include "System.hpp"

namespace aos
{
unsigned int System::id = 0;

System::System()
{
    std::cout << "System::System" << std::endl;
}

System::~System()
{
    std::cout << "System::~System" <<std::endl;
}


unsigned int System::push_back(System * subsystem) { return 0; }
void System::pop_back(){ }

void System::render(Uint32 dt_ms, Uint32 time) { }
void System::update(Uint32 dt_ms, Uint32 time) { }

} // END namespace aos
