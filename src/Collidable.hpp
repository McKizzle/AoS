#include <vector>
#include <cmath>
#include <gmtl/VecOps.h>

#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP
namespace aos
{

    class Collidable
    {
        public:
            /// An object will need to implement this method if collision 
            /// detection is needed. 
            virtual bool check_collision(std::vector< double > point) = 0;

            /// Returns the verticies that belong to an object. 
            virtual void get_vertices( std::vector< gmtl::Vec2d > & verts ) = 0;
            virtual void get_center_coords( gmtl::Vec2d & cords ) = 0;
            
            /// Gets the bounding radius of the Object. 
            virtual double get_bounding_radius() = 0;

            /// Determines if a point lies within a triangle. Solves for unkowns $u$ and $v$ in
            /// the formula
            ///
            /// $ P = A + u(B - A) + v(C - A) $
            /// 
            /// \param[in] the point of interest
            /// \param[in] Vertex A
            /// \param[in] Vertex B
            /// \param[in] Vertex C
            /// \param[in, out] u
            /// \param[in, out] v
            /// 
            /// \returns true / false if inside / ouside.
            static bool point_in_triangle(
                std::vector< double > P, std::vector< double > A, 
                std::vector< double > B, std::vector< double > C,
                double &u, double &v
                ); 
            
            
            /// Determines if a point lies within a triangle. Solves for unkowns $u$ and $v$ in
            /// the formula
            ///
            /// $ P = A + u(B - A) + v(C - A) $
            /// 
            /// \param[in] the point of interest
            /// \param[in] Vertex A
            /// \param[in] Vertex B
            /// \param[in] Vertex C
            /// \param[in, out] u
            /// \param[in, out] v
            /// 
            /// \returns true / false if inside / ouside.
            static bool point_in_triangle(
                gmtl::Vec2d P, gmtl::Vec2d A, 
                gmtl::Vec2d B, gmtl::Vec2d C,
                double &u, double &v
                );

            /// Checks for the collision of a point and a circle. 
            /// 
            /// \param[in] Point of interest.
            /// \param[in] Center of circle.
            /// \param[in] radius
            ///
            /// \returns true or false for hit or miss
            static bool point_in_circle(
                gmtl::Vec2d P, gmtl::Vec2d C, double radius);


            /// Checks for the collision of a circle and circle. 
            /// 
            /// \param[in] Center of circle one. 
            /// \param[in] Center of circle two. 
            /// \param[in] Circle one radius. 
            /// \param[in] Circle two radius.
            ///
            /// \returns true or false for hit or miss
            static bool circle_in_circle(
                gmtl::Vec2d C1, gmtl::Vec2d C2, double r1, double r2);


    };
}
#endif
