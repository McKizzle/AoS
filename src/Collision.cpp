#include "Collision.hpp"

namespace aos 
{

Collision::Collision(Collidable *collider) 
{
    this->collider = collider;
}

Collision::~Collision() { }

void Collision::update(Uint32 dt_ms, Uint32 time) 
{
    double r1 = this->collider->get_bounding_radius();
    gmtl::Vec2d C1 = this->collider->get_center_coords();
    std::vector< gmtl::Vec2d > verts = this->collider->get_vertices();
    for(std::vector< System * >::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        Collidable *collidable = (Collidable *)(*it); 
        double r2 = collidable->get_bounding_radius();
        gmtl::Vec2d C2 = collidable->get_center_coords();
        
        /// If the bounding circles collide then loop through each point the collidable object. 
        if(!Collidable::circle_in_circle(C1, C2, r1, r2))
        {
            for(std::vector< gmtl::Vec2d >::iterator it = verts.begin(); it != verts.end(); ++it)
            {
                std::vector< double > point = { (*it)[0], (*it)[1] };
                if(collidable->check_collision(point)) 
                {
                    std::cout << "Collision!!" << std::endl;
                }
            }
        }
    }
}


}
