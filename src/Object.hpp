#include "Renderable.hpp"
#include "Updateable.hpp"
#include "Eventful.hpp"

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
namespace aos {
    /// \class Object Object.hpp
    /// \brief Represents a game object.
    ///  
    /// All objects in the game that need to be rendered and integrated
    /// must inherit from the Object class. 
    class Object: public Renderable, public Updateable, public Eventful
    {
        public:
            /// Contains the state of the object.
            /// 0: x position
            /// 1: y position
            /// 2: x velocity
            /// 2: y velocity
            /// 3: x jerk
            /// 4: y jerk
            /// 5: heading
            /// 6: angular velocity
            /// 7: angualr jerk
            std::vector< double > state; 
            double heading = 0.0; ///< Heading in degrees
            double angular_vel = 0.0; ///< The rotational speed of the object. Positive is clockwise, negative counterclockwise. 
            double heading_accel = 0.0; ///< Accereration of the heading.
            double heading_jerk = 0.0;  ///< Jerk of the heading.
            std::vector< double > velocity;
            std::vector< double > acceleration;
            std::vector< double > jerk;
            std::vector< double > position;
            std::vector< std::vector<double> > vertices;
            std::vector< unsigned int > edges;

            Object();
            ~Object();
            virtual void render(Uint32 dt_ms, Uint32 time);
            virtual void update(Uint32 dt_ms, Uint32 time);

            std::vector< double > * ode(std::vector< double > & x, Uint32 t);
    };
}
#endif


