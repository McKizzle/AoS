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


unsigned int GravityWell::push_back_orbit(System * satellite, double distance, double lax)
{ 
    Object * stllt = (Object *) satellite; 

    double l_dev = -(lax / 2) + (((double) std::rand() / (double) RAND_MAX) * lax);
    double eps_distance = distance + this->epsilon + l_dev; // nudge the distance slighly. 

    double position = ((double) std::rand() / (double) RAND_MAX) * (2 * M_PI);

    // Calculate the new position of the satlite. 
    double x = std::cos(position) * (distance + l_dev);
    double y = std::sin(position) * (distance + l_dev);

    double dx = std::abs(this->celestial_body->state[Object::XIND] - x);
    double theta = position + (M_PI / 2);//(std::acos(dx / distance) * 2.0) + (M_PI / 2);
    double v_0 = std::sqrt((GW_GM * this->mass) / (eps_distance)) * 0.70;
    
    double v_x = v_0 * std::cos(theta);
    double v_y = v_0 * std::sin(theta);

    stllt->state[Object::VXIND] = v_x;
    stllt->state[Object::VYIND] = v_y;
    
    //std::cout << "dx = " << dx << " and distance = " << distance << std::endl;
    //std::cout << "theta: " << theta << std::endl;
    //std::cout << "v_0: " << v_0 << std::endl;
    //std::cout << "( " << v_x << ", " << v_y << ")" << std::endl;

    stllt->state[Object::XIND] = this->celestial_body->state[Object::XIND] + x;
    stllt->state[Object::YIND] = this->celestial_body->state[Object::YIND] + y;
 
    // Push the satellite into the system. 
    return this->push_back(satellite);
}

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

