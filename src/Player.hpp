#include <SDL2/SDL.h>
#include <cmath>
#include <utility>

#define _USE_MATH_DEFINES

#include "includes.hpp"
#include "Object.hpp"
#include "Eventful.hpp"
#include "Ode.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP
namespace aos {
    class Player: public Object
    {
        public: 
            double max_heading_velocity = 500.0; ///< (degrees) Able to rotate two revolutions per second.
            double heading_thrusters_impulse = 1440.0; ///< (degrees) The speed at which the thrusters can decrease the velocity.
            int prev_sign_vheading = 1; ///< keep the state of the heading velocity sign (neg or pos). Should always be one!
            bool heading_key_pressed = false; ///< Remember if the player pressed one of the heading control keys
             
            double max_velocity = 10.0; ///< A maximum of 10 units per second.
            double thrusters_impulse = 15.0; ///< The acceleration that the rockets provide. 
            double thruster_key_pressed = false; ///< Remember if the player pressed one of the thrusters keys.

            Player();
            ~Player();
            //virtual void render(Uint32 dt, Uint32 time);
            virtual void update(Uint32 dt, Uint32 time);
            virtual void send_event(const Uint8 * keyboardStates, Uint32 dt, Uint32 time);
            virtual std::vector< double > * system(Uint32 t, std::vector< double > * x);
            static Player * default_player();
            void test_vectors();
    };
}

#endif
