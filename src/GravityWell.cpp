#include "GravityWell.hpp"

namespace aos
{

GravityWell::GravityWell(Object * celestial_body)
{
    this->epsilon  = pe * celestial_body->bs_r;

    celestial_body->calculate_mass(); // Renitialize the mass just to be safe. 
    this->mass = celestial_body->mass;
    this->celestial_body = celestial_body;
}

GravityWell::~GravityWell()
{
}

unsigned int GravityWell::push_back(System * satellite)
{
    this->satellites.push_back((Object *) satellite);
    return 0;
}

unsigned int GravityWell::push_back_orbit(System * satellite, double distance, double lax)
{ 
    Object * stllt = (Object *) satellite; 

    double l_dev = -(lax / 2) + (((double) std::rand() / (double) RAND_MAX) * lax);
    distance += l_dev;

    double position = ((double) std::rand() / (double) RAND_MAX) * (2 * M_PI);

    // Calculate the new position of the satellite. 
    std::vector< double > xy = this->position_to_celestial_body(distance, position);
    stllt->state[Object::XIND] = xy[0]; 
    stllt->state[Object::YIND] = xy[1]; 

    // Calculate and set the orbital velocity of the satellite. 
    std::vector< double > v_e = this->distance_for_orbital_velocity(distance, position, stllt->mass);
    stllt->state[Object::VXIND] = v_e[0] + this->celestial_body->state[Object::VXIND];
    stllt->state[Object::VYIND] = v_e[1] + this->celestial_body->state[Object::VYIND]; 

 
    // Push the satellite into the system. 
    return this->push_back(satellite);
}

std::vector< double > GravityWell::position_to_celestial_body(double distance, double position)
{
    std::vector< double > xy = {0, 0};
    xy[0] = this->celestial_body->state[Object::XIND] + std::cos(position) * (distance);
    xy[1] = this->celestial_body->state[Object::YIND] + std::sin(position) * (distance);
    return xy;
}

std::vector< double > GravityWell::distance_for_orbital_velocity(double distance, double position, double obj_mass)
{ 
    double theta = position + (M_PI / 2.0);
    double v_e = std::sqrt((GW_GM * (this->mass)) / (distance + this->epsilon)) * 0.70;
    
    double v_x = v_e * std::cos(theta);
    double v_y = v_e * std::sin(theta);

    return {v_x, v_y};
}

void GravityWell::pop_back()
{
    this->satellites.pop_back();
}

std::vector< double > GravityWell::F_g(Object * satellite) 
{ 
    std::vector< double > p_0 = { this->celestial_body->state[Object::XIND], this->celestial_body->state[Object::YIND] }; // point one.
    std::vector< double > p_s = { satellite->state[Object::XIND], satellite->state[Object::YIND] };  // point two.
    std::vector< double > v_s = { p_s[0] - p_0[0], p_s[1] - p_0[1] }; // vector representing the xy distances.
    double r_s = std::sqrt( std::pow(v_s[0], 2) + std::pow(v_s[1], 2) ) + this->epsilon; // euclidean distance. 
    
    std::vector< double > F_s = std::vector< double >(2);
    F_s[0] = -(GW_GM * this->mass * v_s[0] / std::pow(r_s, 3));
    F_s[1] = -(GW_GM * this->mass * v_s[1] / std::pow(r_s, 3));
    return F_s;
}

// TODO: The implementation is wasteful. I am recalculateing variables too many times. 
void GravityWell::update(Uint32 dt_ms, Uint32 time)
{
    for(std::vector<Object *>::iterator it = this->satellites.begin(); it != this->satellites.end(); ++it)
    {
        std::vector< double > F_s = this->F_g(*it);
        (*it)->state[Object::AXIND] += F_s[0];
        (*it)->state[Object::AYIND] += F_s[1];
    }
}


void GravityWell::render(Uint32 dt_ms, Uint32 time) { }
void GravityWell::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time){ }

}

