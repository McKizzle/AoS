#include <vector>

#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "System.hpp"

namespace aos
{
    class Systems: public System
    {
        public:
            std::vector<System *> children; ///< The children of the system.  

            Systems();
            virtual ~Systems();
            virtual unsigned int push_back(System * subsystem); ///< Adds a subsystem. Return assigned ID. 
            virtual void pop_back(); ///< Removes a subsystem. 

            virtual void render(Uint32 dt_ms, Uint32 time); ///< By default simply call the render method for all children. 
            virtual void update(Uint32 dt_ms, Uint32 time); ///< By default simply call the update method for all children. 
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time); ///< By default simply call the send_event for all children. 
    };
}

#endif
