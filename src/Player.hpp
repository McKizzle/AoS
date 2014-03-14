#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <cmath>
#include <utility>

#define _USE_MATH_DEFINES

#include "includes.hpp"
#include "Object.hpp"
#include "Eventful.hpp"

namespace aos {
    class Player: public Object 
    {
        public:
            Player();
            ~Player();
            virtual void render(Uint32 dt, Uint32 time);
            //virtual void update(Uint32 dt, Uint32 time);
            virtual void send_event(const Uint8 * keyboardStates, Uint32 dt, Uint32 time);

            static Player * default_player();

            void test_vectors();
    };
}

#endif
