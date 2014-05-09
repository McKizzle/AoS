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

            /// Clones the current System. 
            //virtual System * clone();

            virtual void render(Uint32 dt_ms, Uint32 time); ///< By default simply call the render method for all children. 
            virtual void update(Uint32 dt_ms, Uint32 time); ///< By default simply call the update method for all children. 
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time); ///< By default simply call the send_event for all children. 
    };
}

#endif
