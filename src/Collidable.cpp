#include <iostream>

#include "Collidable.hpp"

namespace aos 
{

bool Collidable::point_in_triangle(
        std::vector< double > P, std::vector< double > A, 
        std::vector< double > B, std::vector< double > C,
        double &u, double &v
    )
{
    using namespace gmtl;
    Vec2d vP; vP.set(&P[0]);
    Vec2d vA; vA.set(&A[0]);
    Vec2d vB; vB.set(&B[0]);
    Vec2d vC; vC.set(&C[0]);

    Vec2d w_2 = vP - vA;
    Vec2d w_0 = vB - vA;
    Vec2d w_1 = vC - vA;
 
    double w_00 = gmtl::dot(w_0, w_0);
    double w_01 = gmtl::dot(w_0, w_1);
    double w_11 = gmtl::dot(w_1, w_1);
    double w_20 = gmtl::dot(w_2, w_0);
    double w_21 = gmtl::dot(w_2, w_1);

    double denom = (w_00 * w_11 - w_01 * w_01);
    u = ((w_11 * w_20) - (w_01 * w_21)) / denom;
    v = ((w_00 * w_21) - (w_01 * w_20)) / denom;

    if ( (u < 0.0) || (u > 1.0) || (v < 0.0) || (v > 1.0) )
    {
        return false; 
    } else {
        return true;
    }
}

bool Collidable::point_in_triangle(
        gmtl::Vec2d P, gmtl::Vec2d A, 
        gmtl::Vec2d B, gmtl::Vec2d C,
        double &u, double &v
    )
{
    using namespace gmtl;
    Vec2d w_2 = P - A;
    Vec2d w_0 = B - A;
    Vec2d w_1 = C - A;
 
    double w_00 = gmtl::dot(w_0, w_0);
    double w_01 = gmtl::dot(w_0, w_1);
    double w_11 = gmtl::dot(w_1, w_1);
    double w_20 = gmtl::dot(w_2, w_0);
    double w_21 = gmtl::dot(w_2, w_1);

    double denom = (w_00 * w_11 - w_01 * w_01);
    u = ((w_11 * w_20) - (w_01 * w_21)) / denom;
    v = ((w_00 * w_21) - (w_01 * w_20)) / denom;

    if ( (u < 0.0) || (u > 1.0) || (v < 0.0) || (v > 1.0) )
    {
        return false; 
    } else {
        return true;
    }
}


/// Checks for the collision of a point and a circle. 
bool Collidable::point_in_circle(
    gmtl::Vec2d P, gmtl::Vec2d C, double radius
    )
{
    gmtl::Vec2d dx = P - C;

    double distance = std::sqrt(dx[0] * dx[0] + dx[1] * dx[1]);

    return (distance > radius) ? false : true;
}

/// Checks for a collision between two circles
bool Collidable::circle_in_circle(
    gmtl::Vec2d C1, gmtl::Vec2d C2, double r1, double r2
    )
{  
    gmtl::Vec2d dx = C1 - C2;
    double distance = std::sqrt(dx[0] * dx[0] + dx[1] * dx[1]);
    return (distance > (r1 + r2)) ? false : true;
}

}
