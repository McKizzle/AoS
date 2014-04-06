#include <SDL2/SDL.h>

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
            /// \param [in] the event to react to.
            /// \param [in] the time step size
            /// \param [in] the game time
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time) = 0;
    };
}

#endif

