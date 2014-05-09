#include "Player.hpp"

#include <iostream>

using namespace aos;

Player::Player() {}

Player::~Player() {}

void Player::fire()
{
    this->weapon->fire();
}

void Player::notify_hit(Collidable * victim)
{   
    std::cout << "Player::notify_hit" << std::endl;
    //std::cout << victim->isa_invincible() << std::endl;
    //if(!victim->isa_invincible())
    //{
      this->score->incrementScore(15.0);
    //}
}

void Player::update(Uint32 dt_ms, Uint32 time) 
{ 
    // update and fire the weapon. 
    if(weapon != nullptr)
    { 
        this->weapon->update(dt_ms, time);
        if(this->fire_key_pressed)
        {
            //std::cout << "Pulling Trigger" << std::endl;
            this->fire();
        }
    }

    std::vector< double > * old_state = this->copy_state();
    std::vector< double > * new_state = intgr->integrate(this, old_state, dt_ms, time);
     
    // Nudge the ship heading velocity if it is close to zero and the heading thrusters are slowing it down. 
    short sign_vheading = ((*new_state)[VHIND] < 0.0) ? 1 : -1; 
    (*new_state)[VHIND] = (!heading_key_pressed && (sign_vheading != prev_sign_vheading)) ? 0.0 : (*new_state)[VHIND];
     
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
    std::vector< double > &tmp_state = *(this->copy_state());
    /// LEFT RIGHT
    if(keyboardStates[SDL_SCANCODE_A] || keyboardStates[SDL_SCANCODE_D])
    {
        this->heading_key_pressed = true;
        
        if(keyboardStates[SDL_SCANCODE_A]) 
            tmp_state[AHIND] = (this->heading_thrusters_impulse / this->mass) + tmp_state[AHIND];
        else    
            tmp_state[AHIND] = -(this->heading_thrusters_impulse / this->mass) + tmp_state[AHIND];

    } else { 
        this->heading_key_pressed = false;
    }

    /// FORWARD BACKWARDS
    if(keyboardStates[SDL_SCANCODE_W] || keyboardStates[SDL_SCANCODE_S] )
    { 
        this->thruster_key_pressed = true;

        double theta = 2.0 * M_PI * state[HIND] / 360.0;
        double a_x = std::cos(theta) * this->thrusters_impulse / this->mass;
        double ra_x = std::cos(theta) * this->rev_thrusters_impulse / this->mass;
        double a_y = std::sin(theta) * this->thrusters_impulse / this->mass; 
        double ra_y = std::sin(theta) * this->rev_thrusters_impulse / this->mass;

        if(keyboardStates[SDL_SCANCODE_W]) 
        {
            tmp_state[AXIND] = a_x + tmp_state[AXIND];
            tmp_state[AYIND] = a_y + tmp_state[AYIND];
        } else {
            tmp_state[AXIND] = -ra_x + tmp_state[AXIND];
            tmp_state[AYIND] = -ra_y + tmp_state[AYIND];
        }
    } else {
        thruster_key_pressed = false;
    }
    
    if(keyboardStates[SDL_SCANCODE_SPACE]) 
    { 
        this->fire_key_pressed = true;
    } else {
        this->fire_key_pressed = false;
    }
    this->swap_state(&tmp_state);
    delete &tmp_state;
    
}

inline void Player::render(Uint32 dt, Uint32 time)
{
    Object::render(dt, time);
      
    // TODO: Implement the thrusters. 
    ///if(this->is_visible)
    ///{
    ///    glPushMatrix();
    ///    glTranslatef(state[XIND] - camera->x(), state[YIND] - camera->y(), 0.0);
    ///    glRotatef(state[HIND], 0, 0, 1);
    ///    glBegin(GL_LINES);  
    ///        glColor3f(color[0], color[1], color[2]);
    ///        for(std::vector< unsigned int>::iterator it = this->edges.begin(); it != edges.end(); ++it)
    ///        {
    ///            glVertex2f((GLfloat)vertices[*it][0], (GLfloat)vertices[*it][1]);
    ///        }
    ///    glEnd();
    ///    glPopMatrix();
    ///}
}


inline void Player::set_collision(Collidable * collider)
{
    Object::set_collision(collider); 
    
    this->score->incrementScore(-10.0);

    /// Now hope that the Systems manager gets the player ship out of there asap. 
    //this->systems_manager->respawn(self);
}

Player * Player::default_player()
{   
    Player *plyr2 = new Player();

    plyr2->add_vertex(1.5, 0.0);
    double theta = 2.0 * M_PI / 3.0; //one-third of 2pi
    plyr2->add_vertex(std::cos(theta), std::sin(theta));
    plyr2->add_vertex(-1.0/4.0, 0.0);
    theta = 4.0 * M_PI / 3.0; // two-thirds of 2pi`
    plyr2->add_vertex(std::cos(theta), std::sin(theta));
    
    plyr2->add_edge(0, 1);
    plyr2->add_edge(1, 2);
    plyr2->add_edge(2, 3);
    plyr2->add_edge(3, 0);

    /// Create the forward thrusters. 

    /// Crate the heading thrusters. 

    /// Create the reverse thrusters. 

    plyr2->balance();


    plyr2->calculate_mass();
    
    return plyr2;
}


