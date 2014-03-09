#include "Renderable.hpp"
#include "Updateable.hpp"
#include "Eventful.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>


#ifndef OBJECT_HPP
#define OBJECT_HPP
namespace aos {
    /// \class Object Object.hpp
    /// \brief Represents a game object.
    ///  
    /// All objects in the game that need to be rendered and integrated
    /// must inherit from the Object class. 
    class Object: public Renderable, public Updateable
    {
        public:
            std::vector< double > angular_momentum;
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
    };
}
#endif


