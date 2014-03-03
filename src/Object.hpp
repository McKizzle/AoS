#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Updateable.hpp"
#include "Renderable.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
namespace aos {
    /// \class Object Object.hpp
    /// \brief Represents a game object.
    ///  
    /// All objects in the game that need to be rendered and integrated
    /// must inherit from the Object class. 
    class Object: public Renderable, public Updateable {
        public:
            float angular_momentum[2];
            float velocity[2];
            float acceleration[2];
            float jerk[2];
            float position[2];
            float * verticies;
            int verticies_dim[2];
            int * edges;
            int edges_dim[2];

            Object();
            ~Object();
            void render(Uint32 dt_ms, Uint32 time);
            void update(Uint32 dt_ms, Uint32 time);
    };
}
#endif


