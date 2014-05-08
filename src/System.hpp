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

            /// Pushes back a system. 
            /// \param [in] a pointer to the system to use. 
            ///
            /// \return the id of the system that was pushed back. Otherwise return 0. 
            virtual unsigned int push_back(System * subsystem); ///< Adds a subsystem. Return assigned ID. 

            /// Pops the last system in the systems. 
            ///
            /// \return the popped system. If not there return a nullptr. 
            virtual System * pop_back(); ///< Removes a subsystem. 

            /// Removes a subsystem by the specified id. (refer to sys_id)
            /// \param [in] id
            ///
            /// \return the removed system pointer. If not found return a nullptr.
            virtual System * erase(unsigned int id); 

            virtual void render(Uint32 dt_ms, Uint32 time);
            virtual void update(Uint32 dt_ms, Uint32 time);
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time); ///< Inherited from Eventful
    };
}
#endif

