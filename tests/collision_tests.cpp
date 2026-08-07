#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Collision
#include <boost/test/unit_test.hpp>

#include <vector>
#include <cmath>

#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Collision.hpp>
#include <Collidable.hpp>
#include <utils.hpp>
 
BOOST_AUTO_TEST_SUITE(Collision)

BOOST_AUTO_TEST_CASE(PointTriangleCollision1)
{
    std::vector< double > p = {0.25, 0.25};
    std::vector< double > p0  = {0.0, 0.0};
    std::vector< double > p1  = {1.0, 0.0};
    std::vector< double > p2  = {0.0, 1.0};

    glm::dvec2 P, A, B, C;
    P = glm::make_vec2(&p[0]);
    A = glm::make_vec2(&p0[0]);
    B = glm::make_vec2(&p1[0]);
    C = glm::make_vec2(&p2[0]);

    double u = 0, v = 0;

    bool collision = aos::Collidable::point_in_triangle(P, A, B, C, u, v);

    BOOST_CHECK_MESSAGE(collision == true, 
        "Collision test failed P = (0.25, 0.25) for ((0.0, 0.0), (1.0, 0.0), (0.0, 1.0))  The calculated u and v are " << u << " and " << v
        );
}

BOOST_AUTO_TEST_CASE(PointTriangleCollision2)
{
    std::vector< double > p = {-0.25, 0.25};
    std::vector< double > p0  = {0.0, 0.0};
    std::vector< double > p1  = {1.0, 0.0};
    std::vector< double > p2  = {0.0, 1.0};

    glm::dvec2 P, A, B, C;
    P = glm::make_vec2(&p[0]);
    A = glm::make_vec2(&p0[0]);
    B = glm::make_vec2(&p1[0]);
    C = glm::make_vec2(&p2[0]);

    double u = 0, v = 0;

    bool collision = aos::Collidable::point_in_triangle(P, A, B, C, u, v);

    BOOST_CHECK_MESSAGE(collision == false, 
        "Collision test failed P = (-0.25, 0.25) for ((0.0, 0.0), (1.0, 0.0), (0.0, 1.0)) The calculated u and v are " << u << " and " << v
        );
}

BOOST_AUTO_TEST_CASE(PointTriangleCollision3)
{
    std::vector< double > p = {-0.25, -0.25};
    std::vector< double > p0  = {0.0, 0.0};
    std::vector< double > p1  = {1.0, 0.0};
    std::vector< double > p2  = {0.0, 1.0};

    glm::dvec2 P, A, B, C;
    P = glm::make_vec2(&p[0]);
    A = glm::make_vec2(&p0[0]);
    B = glm::make_vec2(&p1[0]);
    C = glm::make_vec2(&p2[0]);

    double u = 0, v = 0;

    bool collision = aos::Collidable::point_in_triangle(P, A, B, C, u, v);

    BOOST_CHECK_MESSAGE(collision == false, 
        "Collision test failed P = (-0.25, -0.25) for ((0.0, 0.0), (1.0, 0.0), (0.0, 1.0)). The calculated u and v are " << u << " and " << v
        );
}

BOOST_AUTO_TEST_CASE(PointTriangleCollision4)
{
    std::vector< double > p = {0.25, -0.25};
    std::vector< double > p0  = {0.0, 0.0};
    std::vector< double > p1  = {1.0, 0.0};
    std::vector< double > p2  = {0.0, 1.0};

    glm::dvec2 P, A, B, C;
    P = glm::make_vec2(&p[0]);
    A = glm::make_vec2(&p0[0]);
    B = glm::make_vec2(&p1[0]);
    C = glm::make_vec2(&p2[0]);

    double u = 0, v = 0;

    bool collision = aos::Collidable::point_in_triangle(P, A, B, C, u, v);

    BOOST_CHECK_MESSAGE(collision == false, 
        "Collision test failed P = (0.25, -0.25) for ((0.0, 0.0), (1.0, 0.0), (0.0, 1.0)) The calculated u and v are " << u << " and " << v
        );
}

BOOST_AUTO_TEST_CASE(PointTriangleCollision5)
{
    std::vector< double > p = {0.00, 0.90};
    std::vector< double > p0  = {0.0, 0.0};
    std::vector< double > p1  = {1.0, 0.0};
    std::vector< double > p2  = {0.0, 1.0};

    glm::dvec2 P, A, B, C;
    P = glm::make_vec2(&p[0]);
    A = glm::make_vec2(&p0[0]);
    B = glm::make_vec2(&p1[0]);
    C = glm::make_vec2(&p2[0]);

    double u = 0, v = 0;

    bool collision = aos::Collidable::point_in_triangle(P, A, B, C, u, v);

    BOOST_CHECK_MESSAGE(collision == true, 
        "Collision test failed P = (0.00, 0.90) for ((0.0, 0.0), (1.0, 0.0), (0.0, 1.0)) The calculated u and v are " << u << " and " << v
        );
}

BOOST_AUTO_TEST_CASE(PointTriangleCollision6)
{
    std::vector< double > p = {1.0, -1.25};
    std::vector< double > p0  = {5.0,  0.0};
    std::vector< double > p1  = {5.0, -5.0};
    std::vector< double > p2  = {0.0, 0.0};

    glm::dvec2 P, A, B, C;
    P = glm::make_vec2(&p[0]);
    A = glm::make_vec2(&p0[0]);
    B = glm::make_vec2(&p1[0]);
    C = glm::make_vec2(&p2[0]);

    double u = 0, v = 0;

    bool collision = aos::Collidable::point_in_triangle(P, A, B, C, u, v);

    BOOST_CHECK_MESSAGE(collision == false, 
        "Collision test failed P = (1.0, -1.25) for ((5.0, 0.0), (5.0, -5.0), (0.0, 0.0)) The calculated u and v are " << u << " and " << v
        );
}

BOOST_AUTO_TEST_CASE(VectorAddition)
{
    std::vector< double > v1 = {0.30, 0.25};
    std::vector< double > v2 = {0.10, 0.10};

    glm::dvec2 g1, g2, g3; 
    g1 = glm::make_vec2(&v1[0]); g2 = glm::make_vec2(&v2[0]);
    
    g3 = g1 + g2;

    BOOST_CHECK_MESSAGE( (g3[0] == 0.40) && (g3[1] == 0.35), "GLM vectors are not addable");
}


BOOST_AUTO_TEST_CASE(VectorRotation)
{
    std::vector< double > v1 = {1.0, 0.0};

    glm::dvec2 g1;
    g1 = glm::make_vec2(&v1[0]);

    double theta = M_PI / 2.0;
    // glm::dmat2 is column-major, so build via the column-major constructor
    // (col0.x, col0.y, col1.x, col1.y) instead of R[row][col] assignment.
    glm::dmat2 R(std::cos(theta), std::sin(theta), -std::sin(theta), std::cos(theta));


    glm::dvec2 g2 = R * g1;
    
    //std::cout << R << std::endl;
    //std::cout << g2[0] << ", " << g2[1] << std::endl;

    BOOST_CHECK_MESSAGE( (g2[0] -  0.0) <= 0.0001 && ((g2[1] - 1.0) <= 0.0001), "GLM Rotation Success");
}

BOOST_AUTO_TEST_CASE(CirclePointCollision0)
{
    std::vector< double > p = {1.0, 1.0};
    std::vector< double > pc = {0.0, 0.0};
    double radius = 1;

    glm::dvec2 P, C;
    P = glm::make_vec2(&p[0]);
    C = glm::make_vec2(&pc[0]); 

    bool inside = aos::Collidable::point_in_circle(P, C, radius);

    BOOST_CHECK_MESSAGE( inside == false,  "Point should be outside of the circle.");
}

BOOST_AUTO_TEST_CASE(CirclePointCollision1)
{
    std::vector< double > p = {0.5, 0.5};
    std::vector< double > pc = {0.0, 0.0};
    double radius = 1;

    glm::dvec2 P, C;
    P = glm::make_vec2(&p[0]);
    C = glm::make_vec2(&pc[0]); 

    bool inside = aos::Collidable::point_in_circle(P, C, radius);

    BOOST_CHECK_MESSAGE( inside == true,  "Point should be outside of the circle.");
}

BOOST_AUTO_TEST_CASE(CirclePointCollision2)
{
    std::vector< double > p = {-0.5, 0.5};
    std::vector< double > pc = {10.0, 10.0};
    double radius = 1;

    glm::dvec2 P, C;
    P = glm::make_vec2(&p[0]);
    C = glm::make_vec2(&pc[0]); 

    bool inside = aos::Collidable::point_in_circle(P, C, radius);

    BOOST_CHECK_MESSAGE( inside == false,  "Point should be outside of the circle.");
}

BOOST_AUTO_TEST_CASE(CircleCircleCollision1)
{
    std::vector< double > p1 = {0.0, 0.0};
    std::vector< double > p2 = {1.25, 10.25};
    double r1 = 1.0;
    double r2 = 1.0;

    glm::dvec2 C1, C2;
    C1 = glm::make_vec2(&p1[0]);
    C2 = glm::make_vec2(&p2[0]); 

    bool inside = aos::Collidable::circle_in_circle(C1, C2, r1, r2);

    BOOST_CHECK_MESSAGE( inside == false,  "Circles should not intersect.");
}

BOOST_AUTO_TEST_CASE(CircleCircleCollision2)
{
    std::vector< double > p1 = {0.0, 0.0};
    std::vector< double > p2 = {1.25, 1.25};
    double r1 = 1.0;
    double r2 = 2.0;

    glm::dvec2 C1, C2;
    C1 = glm::make_vec2(&p1[0]);
    C2 = glm::make_vec2(&p2[0]); 

    bool inside = aos::Collidable::circle_in_circle(C1, C2, r1, r2);

    BOOST_CHECK_MESSAGE( inside == true,  "Circles should intersect.");
}


BOOST_AUTO_TEST_SUITE_END()


