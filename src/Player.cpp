#include "Player.hpp"

using namespace aos;

Player::Player()
{ 
}

Player::~Player() 
{ 
}

void Player::update(Uint32 dt_ms, Uint32 time) 
{ 
    std::vector< double > * old_state = this->copy_state();
    std::vector< double > * new_state = intgr->integrate(this, old_state, dt_ms, time);
    
    // Nudge the ship heading velocity if it is close to zero and the heading thrusters are slowing it down. 
    short sign_vheading = ((*new_state)[VHIND] < 0.0) ? 1 : -1; 
    (*new_state)[VHIND] = (!heading_key_pressed && (sign_vheading != prev_sign_vheading)) ? 0.0 : (*new_state)[VHIND];
    heading_key_pressed = false;
    thruster_key_pressed= false;
     
    // Change current state values
    (*new_state)[AXIND] = 0.0;
    (*new_state)[AYIND] = 0.0;
    (*new_state)[AHIND] = 0.0;

    this->swap_state(new_state);
    delete old_state;
    delete new_state;
}

std::vector< double > * Player::system(Uint32 t, std::vector< double > * x)
{
    std::vector< double > * dxdt = new std::vector< double >(x->size(), 0.0);
    
    // Calculate the heading acceleration. 
    short sign_vheading = ((*x)[VHIND] < 0.0) ? 1 : -1; 
    double abs_vheading = std::abs((*x)[VHIND]);
    double d2xdt2_heading = (abs_vheading > max_heading_velocity) ? sign_vheading * heading_thrusters_impulse : (*x)[AHIND];
    if(!heading_key_pressed && (abs_vheading > 0)) 
    { 
        d2xdt2_heading += sign_vheading * heading_thrusters_impulse;
    } 
    prev_sign_vheading = sign_vheading;


    (*dxdt)[XIND]  = (*x)[VXIND];
    (*dxdt)[YIND]  = (*x)[VYIND];
    (*dxdt)[VXIND] = (*x)[AXIND];
    (*dxdt)[VYIND] = (*x)[AYIND];
    (*dxdt)[AXIND] = 0.0;  
    (*dxdt)[AYIND] = 0.0;  
    (*dxdt)[HIND]  = (*x)[VHIND];
    (*dxdt)[VHIND] = d2xdt2_heading; 
    (*dxdt)[AHIND] = 0.0; 
 
    return dxdt;
}

void Player::send_event(const Uint8 * keyboardStates, Uint32 dt, Uint32 time) 
{
    // Acceleration
    double theta = 2.0 * M_PI * state[HIND] / 360.0;
    double a_x = std::cos(theta) * thrusters_impulse;
    double a_y = std::sin(theta) * thrusters_impulse; 
     
    //std::vector< double > tmp_state(state);
    std::vector< double > &tmp_state = *(this->copy_state());
    if(keyboardStates[SDL_SCANCODE_A])
    {
        heading_key_pressed = true;

        tmp_state[AHIND] = heading_thrusters_impulse + tmp_state[AHIND];
    }
    if(keyboardStates[SDL_SCANCODE_W])
    {
        tmp_state[AXIND] = a_x + tmp_state[AXIND];
        tmp_state[AYIND] = a_y + tmp_state[AYIND];

        thruster_key_pressed = true;
    }
    if(keyboardStates[SDL_SCANCODE_D])
    { 
        heading_key_pressed = true;
        
        tmp_state[AHIND] = -heading_thrusters_impulse + tmp_state[AHIND];
    }
    if(keyboardStates[SDL_SCANCODE_S])
    { 
        tmp_state[AXIND] = -a_x / 2.0 + tmp_state[AXIND];
        tmp_state[AYIND] = -a_y / 2.0 + tmp_state[AYIND];

        thruster_key_pressed = true;
    }
    if(keyboardStates[SDL_SCANCODE_SPACE]) 
    { 
    }
    this->swap_state(&tmp_state);
    delete &tmp_state;
    
}

Player * Player::default_player()
{   
    Player *plyr2 = new Player();

    plyr2->add_vertex(1.0, 0.0);
    double theta = 2.0 * M_PI / 3.0; //one-third of 2pi
    plyr2->add_vertex(std::cos(theta), std::sin(theta));
    plyr2->add_vertex(-1.0/3.0, 0.0);
    theta = 4.0 * M_PI / 3.0; // two-thirds of 2pi`
    plyr2->add_vertex(std::cos(theta), std::sin(theta));
    
    plyr2->add_edge(0, 1);
    plyr2->add_edge(1, 2);
    plyr2->add_edge(2, 3);
    plyr2->add_edge(3, 0);

    plyr2->calculate_mass();
    
    return plyr2;
}


