#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Collision
#include <boost/test/unit_test.hpp>

#include <vector>
#include <cmath>

#define _USE_MATH_DEFINES

#include <gmtl/gmtl.h> 
#include <gmtl/VecOps.h>
#include <gmtl/MatrixOps.h>

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

    gmtl::Vec2d P, A, B, C;
    P.set( &p[0]);
    A.set(&p0[0]);
    B.set(&p1[0]);
    C.set(&p2[0]);

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

    gmtl::Vec2d P, A, B, C;
    P.set( &p[0]);
    A.set(&p0[0]);
    B.set(&p1[0]);
    C.set(&p2[0]);

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

    gmtl::Vec2d P, A, B, C;
    P.set( &p[0]);
    A.set(&p0[0]);
    B.set(&p1[0]);
    C.set(&p2[0]);

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

    gmtl::Vec2d P, A, B, C;
    P.set( &p[0]);
    A.set(&p0[0]);
    B.set(&p1[0]);
    C.set(&p2[0]);

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

    gmtl::Vec2d P, A, B, C;
    P.set( &p[0]);
    A.set(&p0[0]);
    B.set(&p1[0]);
    C.set(&p2[0]);

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

    gmtl::Vec2d P, A, B, C;
    P.set( &p[0]);
    A.set(&p0[0]);
    B.set(&p1[0]);
    C.set(&p2[0]);

    double u = 0, v = 0;

    bool collision = aos::Collidable::point_in_triangle(P, A, B, C, u, v);

    BOOST_CHECK_MESSAGE(collision == true, 
        "Collision test failed P = (0.00, 0.90) for ((0.0, 0.0), (1.0, 0.0), (0.0, 1.0)) The calculated u and v are " << u << " and " << v
        );
}

BOOST_AUTO_TEST_CASE(VectorAddition)
{
    std::vector< double > v1 = {0.30, 0.25};
    std::vector< double > v2 = {0.10, 0.10};

    gmtl::Vec2d g1, g2, g3; 
    g1.set(&v1[0]); g2.set(&v2[0]);
    
    g3 = g1 + g2;

    BOOST_CHECK_MESSAGE( (g3[0] == 0.40) && (g3[1] == 0.35), "GMTL vectors are not addable");
}


BOOST_AUTO_TEST_CASE(VectorRotation)
{
    std::vector< double > v1 = {1.0, 0.0};

    gmtl::Vec2d g1;
    g1.set(&v1[0]);

    gmtl::Matrix22d R; // Rotation and translation matrix. 
    double theta = M_PI / 2.0;
    R[0][0] =  std::cos(theta);
    R[0][1] = -std::sin(theta);
    R[1][0] =  std::sin(theta);
    R[1][1] =  std::cos(theta);
    
    gmtl::Vec2d g2 = R * g1;
    
    //std::cout << R << std::endl;
    //std::cout << g2[0] << ", " << g2[1] << std::endl;

    BOOST_CHECK_MESSAGE( (g2[0] -  0.0) <= 0.0001 && ((g2[1] - 1.0) <= 0.0001), "GMTL Rotation Sucess");
}

BOOST_AUTO_TEST_CASE(CirclePointCollision0)
{
    std::vector< double > p = {1.0, 1.0};
    std::vector< double > pc = {0.0, 0.0};
    double radius = 1;

    gmtl::Vec2d P, C;
    P.set(&p[0]);
    C.set(&pc[0]); 

    bool inside = aos::Collidable::point_in_circle(P, C, radius);

    BOOST_CHECK_MESSAGE( inside == false,  "Point should be outside of the circle.");
}

BOOST_AUTO_TEST_CASE(CirclePointCollision1)
{
    std::vector< double > p = {0.5, 0.5};
    std::vector< double > pc = {0.0, 0.0};
    double radius = 1;

    gmtl::Vec2d P, C;
    P.set(&p[0]);
    C.set(&pc[0]); 

    bool inside = aos::Collidable::point_in_circle(P, C, radius);

    BOOST_CHECK_MESSAGE( inside == true,  "Point should be outside of the circle.");
}

BOOST_AUTO_TEST_CASE(CirclePointCollision2)
{
    std::vector< double > p = {-0.5, 0.5};
    std::vector< double > pc = {10.0, 10.0};
    double radius = 1;

    gmtl::Vec2d P, C;
    P.set(&p[0]);
    C.set(&pc[0]); 

    bool inside = aos::Collidable::point_in_circle(P, C, radius);

    BOOST_CHECK_MESSAGE( inside == false,  "Point should be outside of the circle.");
}

BOOST_AUTO_TEST_CASE(CircleCircleCollision1)
{
    std::vector< double > p1 = {0.0, 0.0};
    std::vector< double > p2 = {1.25, 10.25};
    double r1 = 1.0;
    double r2 = 1.0;

    gmtl::Vec2d C1, C2;
    C1.set(&p1[0]);
    C2.set(&p2[0]); 

    bool inside = aos::Collidable::circle_in_circle(C1, C2, r1, r2);

    BOOST_CHECK_MESSAGE( inside == false,  "Circles should not intersect.");
}

BOOST_AUTO_TEST_CASE(CircleCircleCollision2)
{
    std::vector< double > p1 = {0.0, 0.0};
    std::vector< double > p2 = {1.25, 1.25};
    double r1 = 1.0;
    double r2 = 2.0;

    gmtl::Vec2d C1, C2;
    C1.set(&p1[0]);
    C2.set(&p2[0]); 

    bool inside = aos::Collidable::circle_in_circle(C1, C2, r1, r2);

    BOOST_CHECK_MESSAGE( inside == true,  "Circles should intersect.");
}


BOOST_AUTO_TEST_SUITE_END()


