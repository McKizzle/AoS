#include "Collision.hpp"

namespace aos 
{

Collision::Collision(Collidable *collider) 
{
    this->colliders.push_back(collider);
}

Collision::~Collision() { }

void Collision::add_collider(Collidable * collider)
{
    this->colliders.push_back(collider);
}

bool Collision::check_collision(Collidable *collider, Object *collidable)
{
    // Collider Parameters. 
    double r1 = collider->get_bounding_radius(); 
    gmtl::Vec2d C1;
    collider->get_center_coords(C1);
    std::vector< gmtl::Vec2d > clld_verts;
    collider->get_vertices(clld_verts);

    // Collidable Parameters. 
    double r2 = collidable->get_bounding_radius();
    gmtl::Vec2d C2;
    collidable->get_center_coords( C2 );
    
    if(Collidable::circle_in_circle(C1, C2, r1, r2))
    {   
        for(std::vector< gmtl::Vec2d >::iterator it = clld_verts.begin(); it != clld_verts.end(); ++it)
        {
            std::vector< double > point = { (*it)[0], (*it)[1] };
            if(collidable->check_collision(point) == true)
            {
                return true;
            }
        }
    } else {
        return false; 
    } 

    return false; // keep the compiler happy. 
}

void Collision::update(Uint32 dt_ms, Uint32 time) 
{
    for(auto &collider: this->colliders)
    {
        for(auto &collidable: this->children)
        {
            if( collider->isa_collidable() && this->check_collision(collider, (Object *) collidable) )
            {             
                collider->set_collision((Collidable *)collidable);
                ((Object *)collidable)->set_collision(collider);
            }
        }
    }
}

void Collision::render(Uint32 dt_ms, Uint32 time) { }

void Collision::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time){ }


}
