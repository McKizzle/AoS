#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <OpenGL/GL.h>
#elif __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP
namespace aos {
    /// \interface Renderable Renderable.hpp
    /// 
    /// Objects that need to rendered at regular intervals 
    /// will implement the renderable interface.
    class Renderable
    {
        public: 
            /// Renders the object.
            /// \param [in] the time step size.
            /// \param [in] the game time.
            virtual void render(Uint32 dt_ms, Uint32 time) = 0;
    };
}
#endif
