#include "includes.hpp"

#ifndef EVENTFUL_HPP
#define EVENTFUL_HPP
namespace aos {
    /// \interface Eventful Eventful.hpp
    ///
    /// The eventful interface is to be used with any class that is 
    /// predestined to handle SDL_Events. 
    class Eventful
    {
        public: 
            /// Reacts to an SDL_Event
            /// \param the event to react to.
            /// \param the time step size
            /// \param the game time
            virtual void send_event(SDL_Event event, Uint32 dt, Uint32 time) = 0;
    };
}

#endif

