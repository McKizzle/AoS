#include <vector>
#include <iostream>

#ifndef ASTEROIDSONSTEROIDS_HPP
#define ASTEROIDSONSTEROIDS_HPP

#include "System.hpp"
#include "Systems.hpp"
#include "Camera.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Planet.hpp"
#include "GravityWell.hpp" 
#include "Weapon.hpp"
#include "Collision.hpp"
#include "Grid.hpp"
//#include "Circle.hpp"
#include "utils.hpp"

namespace aos
{
    class Player;
    class Planet;
    /// \class AsteroidsOnSteroids
    /// \brief The default game management system. 
    /// 
    /// For simplicty the class will remain limited in scope 
    /// for the class presentation. 
    class AsteroidsOnSteroids: public Systems
    {   
        public:
            Systems * universe;
            std::vector<System *> system_tracker;

            Systems * gravity_systems;
            Systems * collision_systems;
            Systems * render_systems;
            Systems * update_systems;

            Collision *clone_template; // clone this for all of the collidables launched. 

            AsteroidsOnSteroids(
                    Player * player, std::vector< System * > * systems, 
                    Planet * planet, Planet * moon);
            ~AsteroidsOnSteroids();
            
            /// For now push_back assumes that the player fired a shot. Therefore a collision system is 
            /// created for each subsystem.
            unsigned int push_back(System * subsystem); 
            void projectile_collision(System * projectile);
            
            //TODO: set all of the systems. 
            //TODO: init the render system.
            //TODO:   

            // Inherited.
            virtual void render(Uint32 dt_ms, Uint32 time);
            virtual void update(Uint32 dt_ms, Uint32 time);
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time); ///< Inherited from Eventful
    };
}

#endif
