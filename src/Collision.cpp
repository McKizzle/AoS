#include "Collision.hpp"

namespace aos 
{

Collision::Collision(Object * collider) 
{
    this->collider = collider;    
}


Collision::~Collision() {}


void Collision::add_collidable(Object * obj)
{
    collideables.push_back(obj);    
}

void Collision::add_collidables(std::vector< Object * > objs)
{
    collideables.insert(collideables.end(), objs.begin(), objs.end()); 
}

std::vector< double > Collision::test_collision(bool & collided)
{

    std::vector< double > intersection;
    for(std::vector<Object *>::iterator it = collideables.begin(); it != collideables.end(); ++it)
    {
       intersection = Collision::test_object_collision(collider, *it, collided);
       if(collided) return intersection;
    }

    return intersection;
}


std::vector< double > Collision::test_object_collision(Object * obj1, Object * obj2, bool & collided)
{
    //std::cout << "Collision::test_object_collision" << std::endl;
    double p0_x = 0.0, p0_y = 0.0;
    double p1_x = 0.0, p1_y = 0.0;
    double p2_x = 0.0, p2_y = 0.0;
    double p3_x = 0.0, p3_y = 0.0;
    double i_x = 0.0,  i_y = 0.0;

    collided = false;

    // Iterate through the edges in object 1 and determine if there is an intersection in object 2.
    std::vector< unsigned int > & edgs1 = obj1->edges;
    std::vector< std::vector< double > > & vrts1 = obj1->vertices;
    double x1_off = obj1->state[Object::XIND];
    double y1_off = obj1->state[Object::YIND];
    std::vector< unsigned int > & edgs2 = obj2->edges;
    std::vector< std::vector< double > > & vrts2 = obj2->vertices;
    double x2_off = obj2->state[Object::XIND];
    double y2_off = obj2->state[Object::YIND];
    for(std::vector< unsigned int >::iterator it11 = edgs1.begin(); it11 != edgs1.end(); it11 += 2)
    {
        std::vector< unsigned int>::iterator it12 = it11 + 1;
        p0_x = x1_off + vrts1[*it11][0];
        p0_y = y1_off + vrts1[*it11][1];
        p1_x = x1_off + vrts1[*it12][0];
        p1_y = y1_off + vrts1[*it12][1];

        for(std::vector< unsigned int >::iterator it21 = edgs2.begin(); it21 != edgs2.end(); it21 += 2)
        {
            std::vector< unsigned int>::iterator it22 = it21 + 1;
            
            // Initialize the variables to pass into the function. 
            p2_x = x2_off + vrts2[*it21][0];
            p2_y = y2_off + vrts2[*it21][1];
            p3_x = x2_off + vrts2[*it22][0];
            p3_y = y2_off + vrts2[*it22][1];
            collided = Collision::test_segment_collision(p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, p3_x, p3_y, &i_x, &i_y);

            //std::cout << p0_x << " " << p0_y << std::endl;
            //std::cout << p1_x << " " << p1_y << std::endl;
            //std::cout << p2_x << " " << p2_y << std::endl;
            //std::cout << p3_x << " " << p3_y << std::endl;
            //std::exit(0);
            if(collided) break;
             
        }
        if(collided) break;
    }
    
    return std::vector< double >(i_x, i_y);
}

bool Collision::test_segment_collision(
        double p0_x, double p0_y, 
        double p1_x, double p1_y, 
        double p2_x, double p2_y, 
        double p3_x, double p3_y, 
        double *i_x, double *i_y)
{
    //std::cout << "\tCollision::test_segment_collision" << std::endl;
    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    double s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return true;
    }

    return false;
}

}
