#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <SDL2/SDL.h>

#include <vector>

#include "Updateable.hpp"
#include "Renderable.hpp"
#include "Object.hpp"

namespace aos
{    
    class System: public Updateable, public Renderable
    {
        public:
            std::vector< Object > objects;
            System();
            ~System();
            void render(Uint32 dt_ms, Uint32 time);
            void update(Uint32 dt_ms, Uint32 time);
    };
}
#endif
