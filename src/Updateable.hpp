#include <SDL2/SDL.h>

#ifndef UPDATEABLE_HPP 
#define UPDATEABLE_HPP
namespace aos {
    /// \interface Updateable Updateable.hpp
    /// 
    /// The Updateable interface will be used by all objects that
    /// need to be updated on a regular basis by the game. 
    class Updateable 
    {
        public:
            /// Updates the object.
            /// \param [in] the time step size.
            /// \param [in] the game time.
            virtual void update(Uint32 dt, Uint32 time) = 0;
    };
}
#endif
