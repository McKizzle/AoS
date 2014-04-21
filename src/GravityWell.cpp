#include "GravityWell.hpp"

namespace aos
{

GravityWell::GravityWell(Object * celestial_body)
{
    std::cout << "GravityWell::GravityWell" << std::endl;
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

void GravityWell::pop_back()
{
    this->satellites.pop_back();
}

void GravityWell::update(Uint32 dt_ms, Uint32 time)
{
    //std::cout << "GravityWell::update" << std::endl;
    // TODO: Apply forces to satilite objects. 
    std::vector< double > p_0 = { this->celestial_body->state[Object::XIND], this->celestial_body->state[Object::YIND] };
    for(std::vector<Object *>::iterator it = this->satellites.begin(); it != this->satellites.end(); ++it)
    {
        std::vector< double > p_s = { (*it)->state[Object::XIND], (*it)->state[Object::YIND] }; 
        std::vector< double > v_s = { p_s[0] - p_0[0], p_s[1] - p_0[1] };
        double r_s = std::sqrt( std::pow(v_s[0], 2) + std::pow(v_s[1], 2) ); 
        std::vector< double > F_s = std::vector< double >(2);
        F_s[0] = -(GW_GM * this->mass * v_s[0] / std::pow(r_s, 3));
        F_s[1] = -(GW_GM * this->mass * v_s[1] / std::pow(r_s, 3));

        if(time % 10 == 0) {
            std::cout << "F_s1: " << F_s[0] << std::endl;
            std::cout << "F_s2: " << F_s[1] << std::endl;
        }

        (*it)->state[Object::AXIND] += F_s[0];
        (*it)->state[Object::AYIND] += F_s[1]; 
    }
}

}

