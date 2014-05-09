#include <SDL2/SDL.h>
#include <cmath>
#include <utility>
#include <vector>
#include <mutex> //Testing thread locking. 

#define _USE_MATH_DEFINES

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Object.hpp"
#include "Score.hpp"
#include "Weapon.hpp"

namespace aos {
    class Weapon;

    class Player: public Object
    {
        public: 
            double max_heading_velocity = 500.0; ///< (degrees) Able to rotate two revolutions per second.
            double heading_thrusters_impulse = 1080.0; ///< (degrees) The speed at which the thrusters can decrease the velocity.
            int prev_sign_vheading = 1; ///< keep the state of the heading velocity sign (neg or pos). Should always be one!
            bool heading_key_pressed = false; ///< Remember if the player pressed one of the heading control keys
             
            double max_velocity = 10.0; ///< A maximum of 10 units per second.
            double thrusters_impulse = 40.0; ///< The acceleration that the rockets provide. 
            double rev_thrusters_impulse = 10.0; ///< The reverse thruster impulse.
            double thruster_key_pressed = false; ///< Remember if the player pressed one of the thrusters keys.

            bool fire_key_pressed = false;
            bool respawn = false;

            Score * score;
            Weapon * weapon = nullptr;
            
            Player();
            ~Player();

            /// Fire weapon
            virtual void fire();
            /// Notify the player of projectile collision
            virtual void notify_hit(Collidable * victim);

            virtual void render(Uint32 dt, Uint32 time);
            virtual void update(Uint32 dt, Uint32 time);
            virtual void send_event(const Uint8 * keyboardStates, Uint32 dt, Uint32 time);
            virtual std::vector< double > * system(Uint32 t, std::vector< double > * x);
            static Player * default_player();
            void test_vectors();

            void set_collision(Collidable * collider); /// Update the score of the player. 
    };
}

#endif
