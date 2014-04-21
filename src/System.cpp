#include "System.hpp"

namespace aos
{
unsigned int System::autonumber = 0;

System::System()
{
    std::cout << "System::System" << std::endl;
    this->sys_id = System::autonumber;
    System::autonumber++;
    std::cout << "ID: " << this->sys_id << std::endl;
}

System::~System()
{
    std::cout << "System::~System" <<std::endl;
}

unsigned int System::push_back(System * subsystem) { return 0; }
void System::pop_back(){ }

void System::render(Uint32 dt_ms, Uint32 time) { }
void System::update(Uint32 dt_ms, Uint32 time) { }
void System::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time) { }

} // END namespace aos
