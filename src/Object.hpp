#include "Renderable.hpp"
#include "Updateable.hpp"
#include "Eventful.hpp"
#include "Ode.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#elif __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifndef OBJECT_HPP
#define OBJECT_HPP
namespace aos 
{
    /// \class Object Object.hpp
    /// \brief Represents a game object.
    ///  
    /// All objects in the game that need to be rendered and integrated
    /// must inherit from the Object class. 
    class Object: public Renderable, public Updateable, public Eventful, public Integratable

    {
        public:
            static const unsigned int XIND = 0; ///< x position index
            static const unsigned int YIND = 1; ///< y position index
            static const unsigned int VXIND= 2; ///< x velocity index
            static const unsigned int VYIND= 3; ///< y velocity index
            static const unsigned int AXIND= 4; ///< x acceleration index
            static const unsigned int AYIND= 5; ///< y acceleration index
            static const unsigned int HIND = 6; ///< heading index
            static const unsigned int VHIND= 7; ///< heading velocity index
            static const unsigned int AHIND= 8; ///< heading acceleration index 
            std::vector< double > state; ///< The current state of the object. 

            std::vector< std::vector<double> > vertices;
            std::vector< unsigned int > edges;
            Integrator *intgr;

            Object(); 
            virtual ~Object();
            virtual void render(Uint32 dt_ms, Uint32 time);
            virtual void update(Uint32 dt_ms, Uint32 time);
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time);
            virtual std::vector< double > * system(Uint32 t, std::vector< double > * x);
    };
}
#endif


