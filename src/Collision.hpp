#include <vector>

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Object.hpp"

namespace aos
{    
    class Collision
    {
        public:
            Object *collider; ///< Object to monitor.  
            std::vector< Object * > collideables;
            std::vector< Object * > bins;

            Collision(Object * collider);
            ~Collision(); 
            void add_collidable(Object * obj);
            void add_collidables(std::vector< Object * > objs);
            std::vector< double > test_collision(bool & collided); ///< Tests for a collision. Returns the intersection point. 

            // For now lets simply use these functions. 
            static std::vector<double> test_object_collision(Object * obj1, Object * obj2, bool & collided);
            static bool test_segment_collision(
                    double p0_x, double p0_y, 
                    double p1_x, double p1_y, 
                    double p2_x, double p2_y, 
                    double p3_x, double p3_y, 
                    double *i_x, double *i_y);
    };
}

#endif

