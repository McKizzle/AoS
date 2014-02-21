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
            void render() = 0;
    };
}
#endif
