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
            /// \param the time step size.
            /// \param the game time.
            void update(int dt, int time) = 0;
    };
}
#endif