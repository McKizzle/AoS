#include "GravityWell.hpp"

namespace aos
{

GravityWell::GravityWell(Object * celestial_body)
{
    std::cout << "GravityWell::GravityWell" << std::endl;
    this->epsilon  = pe * celestial_body->bs_r;
    this->mass = std::pow(celestial_body->bs_r, 2) * M_PI * this->density;
    this->celestial_body = celestial_body;
}

GravityWell::~GravityWell()
{
    std::cout << "GravityWell::~GravityWell" << std::endl;
}

unsigned int GravityWell::push_back(System * satellite)
{
    this->satellites.push_back((Object *) satellite);

    std::cout << "GravityWell::push_back" << std::endl;

    return 0;
}


unsigned int GravityWell::push_back_orbit(System * satellite, double distance)
{ 
    Object * stllt = (Object *) satellite; 

    double position = 0.0; //((double) std::rand() / (double) RAND_MAX) * (M_PI / 4.0);

    double x = std::cos(position) * distance;
    double y = std::sin(position) * distance;
    stllt->state[Object::XIND] = this->celestial_body->state[Object::XIND] + x;
    stllt->state[Object::YIND] = this->celestial_body->state[Object::YIND] + y;

    std::cout << "position: " << x << ", " << y << std::endl;
    std::cout << "Distance: " << std::sqrt(std::pow(x, 2) + std::pow(y, 2)) << std::endl;
    
    // Calculate and set the velocity to stay in orbit.
    double v_y = std::sqrt((GW_GM * this->mass ) / (distance + this->epsilon)) * 0.70;

    //stllt->state[Object::VXIND] = v_x;
    stllt->state[Object::VYIND] = v_y;
      
    // Push the satellite into the system. 
    return this->push_back(satellite);
}

//unsigned int GravityWell::push_back_orbit(System * satellite, double distance, double position)
//{
//    Object * stllt = (Object *) satellite; 
//
//    double x = std::cos(position) * distance;
//    double y = std::sin(position) * distance;
//    stllt->state[Object::XIND] = x;
//    stllt->state[Object::YIND] = y;
//
//    std::cout << "position: " << x << ", " << y << std::endl;
//
//    // Calculate and set the velocity to stay in orbit.
//    double v_x = std::sqrt((GW_GM * this->mass) / x);
//    double v_y = std::sqrt((GW_GM * this->mass) / y);
//    
//    std::cout << "velocity: " << v_x << ", " << v_y << std::endl;
//
//    //stllt->state[Object::VXIND] = v_x;
//    //stllt->state[Object::VYIND] = v_y;
//      
//    // Push the satellite into the system. 
//    return this->push_back(satellite);
//}

void GravityWell::pop_back()
{
    this->satellites.pop_back();
}

std::vector< double > GravityWell::F_g(Object * satellite) 
{ 
    std::vector< double > p_0 = { this->celestial_body->state[Object::XIND], this->celestial_body->state[Object::YIND] };
    std::vector< double > p_s = { satellite->state[Object::XIND], satellite->state[Object::YIND] }; 
    std::vector< double > v_s = { p_s[0] - p_0[0], p_s[1] - p_0[1] };
    double r_s = std::sqrt( std::pow(v_s[0], 2) + std::pow(v_s[1], 2) ) + this->epsilon; 
    
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

}

