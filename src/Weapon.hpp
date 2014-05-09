#include <cmath>

#define _USE_MATH_DEFINES

#define DEG2RAD( deg ) deg * 2.0 * M_PI / (360.0)


#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "System.hpp"
#include "Ode.hpp"
#include "Player.hpp"
#include "Object.hpp"
#include "Projectile.hpp"

namespace aos
{ 
    class Player;
    class Object;
    class Projectile;

    ///\class Weapon Weapon.hpp
    ///\brief Manages projectiles and launches them. 
    class Weapon: public System, public Integratable
    {
        public:
            Player *owner; // The owner of the weapon.

            std::vector< Projectile * > ammo_round;
            unsigned int next_round = 0;
             
            double hit_score  = 100; // Points to add to the score.
            double min_fire_charge = 1.0; // A what charge a projectile can be fired. 
            double charge_rate = 1.0; // The rate defaults to 4 shots per second. 
            double muzzle_velocity = 20.0; // Launches a projectile at 25 units per second. 
            bool   pull_trigger = false; 
            double  density = 1;
            
            const static int CIND = 0;  // Charge level index. 
            const static int CVIND = 1; // Charge velocity index. 
            std::vector< double > state; // The amount of time to wait before being able to recharge. 

            Integrator *intgr;                  ///< Handles the integration of the object. 

            Weapon(Player * owner, std::vector<Projectile *> *ammunition); // Needs an owner.
            virtual ~Weapon();
            
            /// Tell the weapon to launch a projectile on it's next update. 
            virtual void fire();
            /// Notify the player of projectile collision
            virtual void notify_hit(Collidable * victim);
            virtual void launch_projectile();

            virtual void update(Uint32 dt_ms, Uint32 time);
            virtual std::vector< double > * system(Uint32 t, std::vector< double > * x);
    };
}

#endif


