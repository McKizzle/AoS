#include "System.hpp"

namespace aos
{
unsigned int System::autonumber = 1;

System::System()
{
    this->sys_id = System::autonumber;
    System::autonumber++;
}

System::~System()
{
}

inline unsigned int System::push_back(System * subsystem) { return 0; }
inline System * System::pop_back() { return nullptr; }
inline System * System::erase(unsigned int id) { return nullptr; }

inline void System::render(Uint32 dt_ms, Uint32 time) { }
inline void System::update(Uint32 dt_ms, Uint32 time) { }
inline void System::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time) { }

} // END namespace aos
