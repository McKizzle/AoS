#include <SDL2/SDL.h>
#include <iostream>

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Updateable.hpp"
#include "Renderable.hpp"
#include "Eventful.hpp"

namespace aos
{
    class System: public Updateable, public Renderable, public Eventful
    {
        public:
            static unsigned int autonumber; ///< Prevent duplicate ids. 
            unsigned int sys_id = 0; ///< Unique ID for the system object. 

            System();
            virtual ~System();
            virtual unsigned int push_back(System * subsystem); ///< Adds a subsystem. Return assigned ID. 
            virtual void pop_back(); ///< Removes a subsystem. 

            virtual void render(Uint32 dt_ms, Uint32 time);
            virtual void update(Uint32 dt_ms, Uint32 time);
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time); ///< Inherited from Eventful
    };
}
#endif

