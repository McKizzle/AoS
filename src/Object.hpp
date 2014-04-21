#include <SDL2/SDL.h>
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

#include "Camera.hpp"
#include "Ode.hpp"
#include "System.hpp"

namespace aos 
{
    class Camera;
    class System;
    
    /// \class Object Object.hpp
    /// \brief Represents a game object.
    ///  
    /// All objects in the game that need to be rendered and integrated
    /// must inherit from the Object class. 
    class Object: public System, public Integratable
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
            std::vector< double > state;        ///< The current state of the object. 
            Integrator *intgr;                  ///< Handles the integration of the object. 

            std::vector< float > color = {1.0, 1.0, 1.0, 1.0}; ///< The color of the object. 

            std::vector< std::vector<double> > vertices; ///< All of the vertices in the object. 
            std::vector< unsigned int > edges; ///< An even-length vector of the vertices to edges. 
            double bs_r = 0.0; ///< The minimum bounding radius. 

            Camera *camera; ///< Used to render the object position relative to the camera. 

            Object(); 
            virtual ~Object();
            virtual void render(Uint32 dt_ms, Uint32 time); ///< Inherited from Renderable
            virtual void update(Uint32 dt_ms, Uint32 time); ///< Inherited from Updatable
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time); ///< Inherited from Eventful
            virtual std::vector< double > * system(Uint32 t, std::vector< double > * x); ///< Inherited from Integratable. 

            /// Adds a vertex (x, y) to the object. 
            /// \param [in] x 
            /// \param [in] y 
            virtual void add_vertex(double x, double y);
            
            /// Adds an edge to the vertex. Instead of actual edges. Expects an index to the 
            /// vertex in the vertices array. 
            /// \param [in] index to the first vertex.
            /// \param [in] index to the second vertex. 
            virtual void add_edge(unsigned int v1,unsigned int v2);

            virtual unsigned int push_back(System * subsystem);
            virtual void pop_back();
    };
}
#endif


