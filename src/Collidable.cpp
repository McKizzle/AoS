#include <iostream>

#include "Collidable.hpp"

namespace aos 
{

bool Collidable::point_in_triangle(
        glm::dvec2 P, glm::dvec2 A,
        glm::dvec2 B, glm::dvec2 C,
        double &u, double &v
    )
{
    using namespace glm;
    dvec2 w_2 = P - A;
    dvec2 w_0 = B - A;
    dvec2 w_1 = C - A;

    double w_00 = glm::dot(w_0, w_0);
    double w_01 = glm::dot(w_0, w_1);
    double w_11 = glm::dot(w_1, w_1);
    double w_20 = glm::dot(w_2, w_0);
    double w_21 = glm::dot(w_2, w_1);

    double denom = (w_00 * w_11 - w_01 * w_01);
    u = ((w_11 * w_20) - (w_01 * w_21)) / denom;
    v = ((w_00 * w_21) - (w_01 * w_20)) / denom;

    if ( (u < 0.0) || (u > 1.0) || (v < 0.0) || (v > 1.0) || (u + v > 1))
    {
        return false; 
    } else {
        return true;
    }
}


/// Checks for the collision of a point and a circle. 
bool Collidable::point_in_circle(
    glm::dvec2 P, glm::dvec2 C, double radius
    )
{
    glm::dvec2 dx = P - C;

    double distance = std::sqrt(dx[0] * dx[0] + dx[1] * dx[1]);

    return (distance > radius) ? false : true;
}

/// Checks for a collision between two circles
bool Collidable::circle_in_circle(
    glm::dvec2 C1, glm::dvec2 C2, double r1, double r2
    )
{
    glm::dvec2 dx = C1 - C2;
    double distance = std::sqrt(dx[0] * dx[0] + dx[1] * dx[1]);
    return (distance > (r1 + r2)) ? false : true;
}

}
