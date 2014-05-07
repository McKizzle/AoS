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
    
    gmtl::Vec2d C1;
    this->collider->get_center_coords(C1);
    
    std::vector< gmtl::Vec2d > clld_verts;
    this->collider->get_vertices(clld_verts);
    
    for(std::vector< System * >::iterator it = this->children.begin(); it != this->children.end(); ++it)
    {
        Object *collidable = (Object *) (*it);

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
                    std::cout << "Collision with: " << ((System *) collidable)->sys_id << std::endl;
                }
            }
        }
        else {}
    }
}

void Collision::render(Uint32 dt_ms, Uint32 time) { }

void Collision::send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time){ }


}
