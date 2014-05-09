#include "Projectile.hpp"

namespace aos 
{

Projectile::Projectile() 
{
    this->owner = owner; 
    
    double r = 0.25;
    this->add_vertex(r, 0.0);
    double theta = 2.0 * M_PI / 3.0; //one-third of 2pi
    this->add_vertex(std::cos(theta) * r, std::sin(theta) * r);
    theta = 4.0 * M_PI / 3.0; // two-thirds of 2pi`
    this->add_vertex(std::cos(theta) * r, std::sin(theta) * r);

    this->add_edge(0, 1);
    this->add_edge(1, 2);
    this->add_edge(2, 0);

    this->is_visible = false;
    this->is_collidable = false;
}

Projectile::~Projectile() { }


void Projectile::set_collision(Collidable * collider)
{
    this->is_visible = false;
    this->is_collidable = false;
    /// Notify the owner of its collision
    std::cout<< "Projectile::set_collision" << std::endl;
    this->owner->notify_hit(collider);
}

}
