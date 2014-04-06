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
            static unsigned int id;

            System();
            virtual ~System();
            virtual unsigned int push_back(System * subsystem) = 0; ///< Adds a subsystem. Return assigned ID. 
            virtual void pop_back() = 0; ///< Removes a subsystem. 

            virtual void render(Uint32 dt_ms, Uint32 time);
            virtual void update(Uint32 dt_ms, Uint32 time);
    };
}
#endif
