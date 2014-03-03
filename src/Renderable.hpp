#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <SDL2/SDL.h>

namespace aos {
    /// \interface Renderable Renderable.hpp
    /// 
    /// Objects that need to rendered at regular intervals 
    /// will implement the renderable interface.
    class Renderable
    {
        public:
            virtual void render(Uint32 dt_ms, Uint32 time) = 0;
    };
}
#endif
