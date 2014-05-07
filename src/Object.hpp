#include <SDL2/SDL.h>
#include <vector>
#include <mutex>

#include <gmtl/gmtl.h>
#include <gmtl/VecOps.h>
#include <gmtl/MatrixOps.h>

#ifdef __APPLE__
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#elif __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define _USE_MATH_DEFINES

#define DEG2RAD( deg ) deg * 2.0 * M_PI / (360.0)

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Camera.hpp"
#include "Ode.hpp"
#include "System.hpp"
#include "Collidable.hpp"

namespace aos 
{
    class Camera;
    class System;
    class Collidable;
    
    /// \class Object Object.hpp
    /// \brief Represents a game object.
    ///  
    /// All objects in the game that need to be rendered and integrated
    /// must inherit from the Object class. 
    class Object: public System, public Integratable, public Collidable
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
            std::mutex swap_state_lock;         ///< When switching a new state
            std::vector< double > state;        ///< The current state of the object. 
            Integrator *intgr;                  ///< Handles the integration of the object. 

            std::vector< float > color = {1.0, 1.0, 1.0, 1.0}; ///< The color of the object. 

            std::vector< std::vector<double> > vertices; ///< All of the vertices in the object. 
            std::vector< unsigned int > edges; ///< An even-length vector of the vertices to edges. 
            double bs_r = 1.0; ///< The minimum bounding radius. 
            double density = 1.0; ///< The density per unit squared in the object. 
            double mass = 1.0; ///< The mass of the object. (this is calculated automatically based on the densicyt)

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
            
            ///Find the center point of all of the vertices. Not to be confused with the center
            /// of gravity. 
            /// \returns a vector of the central x and y values. 
            virtual std::vector< double > vertex_average();

            /// Balances the vertices about the vertex avarage
            virtual void balance();
            
            /// Calculates the mass of the object. This function assumes that the entire object
            /// is a set of triangles which have a single point at the object's origin. It takes
            /// the sum of their areas and calculats the mass based on the object density. 
            virtual void calculate_mass();
            
            /// Adds an edge to the vertex. Instead of actual edges. Expects an index to the 
            /// vertex in the vertices array. 
            /// \param [in] index to the first vertex.
            /// \param [in] index to the second vertex. 
            virtual void add_edge(unsigned int v1,unsigned int v2);

            virtual unsigned int push_back(System * subsystem);
            virtual void pop_back(); ///< Inherited from System
            virtual void swap_state(std::vector< double > * new_state); ///< Thread-safe swap operation. 
            virtual std::vector< double > * copy_state(); ///< Thread-safe swap operation. 


            /// Collision Detection Collidable interface. 
            virtual bool check_collision(std::vector< double > point);
            virtual double get_bounding_radius();
            virtual void get_vertices( std::vector< gmtl::Vec2d > & verts );
            virtual void get_center_coords( gmtl::Vec2d & cords );
    };
}
#endif


