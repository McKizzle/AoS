#include "Planet.hpp"

namespace aos
{

Planet::Planet(double radius, unsigned int sectors, double x, double y)
{
    this->state[Object::XIND] = x;
    this->state[Object::YIND] = y;

    //construct the verticies
    for(unsigned int i = 0; i < sectors; i++)
    {
        double theta = (double) i * 2.0 * M_PI / (double) sectors; 
        this->add_vertex(radius * std::cos(theta), radius * std::sin(theta));
    }
    //construct the edges
    for(unsigned int idx1 = 0; idx1 < sectors; idx1++)
    {
        unsigned int idx2 = (idx1 + 1) % sectors;
        this->add_edge(idx1, idx2);
    }
    
    this->bs_r = radius; // Set the bounding radius. 
}

Planet::~Planet() { }

bool Planet::check_collision(std::vector< double > point)
{
    gmtl::Vec2d p0, p1, dp;
    p0.set(&(this->state[Object::XIND]));
    p1.set(&point[0]);

    dp = p1 - p0;

    double dist = std::sqrt(dp[0] * dp[0] + dp[1] * dp[1]);

    if(dist > this->bs_r)
        return false && this->is_collidable;
    else
        return true;
}

inline void Planet::set_collision(Collidable * collider)
{
    // TODO: Act on the collision. 
    this->collider = collider; 

    // Decrement the score. 
}

}
