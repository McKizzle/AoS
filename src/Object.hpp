#ifndef OBJECT_HPP
#define OBJECT_HPP
namespace aos {
    /// \class Object Object.hpp
    /// \brief Represents a game object.
    ///  
    /// All objects in the game that need to be rendered and integrated
    /// must inherit from the Object class. 
    class Object {
        public:
            int angular_momentum[4];
            int velocity[4];
            int acceleration[4];
            int jerk[4];
            int * verticies;
            int * edges;

            Object();
            ~Object();
            virtual int render();
            virtual int update(int dt_ms);
    };
}
#endif


