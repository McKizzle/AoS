#include "Weapon.hpp"

#include<iostream>

namespace aos
{

Weapon::Weapon(Player * owner, std::vector< Projectile *> *ammunition)
{
    this->owner = owner;
    this->state.push_back(min_fire_charge);
    this->state.push_back(charge_rate);

    for(auto &prjtl: (*ammunition))
    {
        prjtl->owner = this;
        prjtl->camera = owner->camera;
        this->ammo_round.push_back(prjtl); 
    }

    intgr = new Integrator();
}

Weapon::~Weapon()
{
    delete intgr;
}

void Weapon::fire()
{
    this->pull_trigger = true; 
}

void Weapon::notify_hit(Collidable * victim)
{
    std::cout<< "Weapon::notify_hit" << std::endl;
    this->owner->notify_hit(victim);     
}

void Weapon::launch_projectile()
{
    // Get the position and velocity and heading of the owner. 
    double h = owner->state[Object::HIND];
    double theta = 2.0 * M_PI * h / 360.0;
    
    // The projectile has a velocity of 
    double pvx = std::cos(theta) * this->muzzle_velocity;
    double pvy = std::sin(theta) * this->muzzle_velocity;

    double px = std::cos(theta) * owner->bs_r;
    double py = std::sin(theta) * owner->bs_r;
    
    // Now we can create a new projectile and pass it to the game manager.
    Projectile *prjtl = ammo_round[(next_round % ammo_round.size())];
    next_round++;

    std::vector< double > *new_state = this->owner->copy_state();
    prjtl->swap_state(new_state);
    
    prjtl->state[Object::XIND] += px;
    prjtl->state[Object::YIND] += py;
    prjtl->state[Object::VXIND] += pvx;
    prjtl->state[Object::VYIND] += pvy; 
    prjtl->state[Object::AXIND] = 0.0;
    prjtl->state[Object::AYIND] = 0.0;

    prjtl->is_visible = true;
    prjtl->is_collidable = true;
}

void Weapon::update(Uint32 dt_ms, Uint32 time) 
{  
    std::vector< double > * old_state = new std::vector< double >(this->state);
    std::vector< double > * new_state = intgr->integrate(this, old_state, dt_ms, time);
    (*new_state)[CIND] = ((*new_state)[CIND] >= min_fire_charge) ? min_fire_charge : (*new_state)[CIND];
    (*new_state)[CVIND] =((*new_state)[CIND] >= min_fire_charge) ? 0.0 : charge_rate ;
    
    (*new_state)[CVIND] = charge_rate;

    // See if we can  fire the weapon.
    bool charged = ((*new_state)[CIND] >= min_fire_charge) ? true : false;
    if(this->pull_trigger && charged)
    {
        std::cout << "Fireing projectile" << std::endl;
        (*new_state)[CIND] = 0.0;
        this->launch_projectile();
    }
    this->pull_trigger = false; 

    this->state.swap(*new_state);
} 

std::vector< double > * Weapon::system(Uint32 t, std::vector< double > * x) 
{ 
    std::vector< double > * dxdt = new std::vector< double >(x->size(), 0.0);

    (*dxdt)[CIND]  = (*x)[CVIND];
    (*dxdt)[CVIND]  = 0.0;

    return dxdt;
}

}
