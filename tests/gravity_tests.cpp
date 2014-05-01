#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Gravity
#include <boost/test/unit_test.hpp>

#include <vector>
#include <cmath>

#include <GravityWell.hpp>
#include <utils.hpp>
 
int add(int i, int j)
{
        return i + j;
} 

BOOST_AUTO_TEST_SUITE(Gravity)

BOOST_AUTO_TEST_CASE(OrbitalPosition)
{
    double planet_radius = 10;
    double satellite_radius = 1;
    aos::Object *planet = aos::circle(planet_radius, 360, 0.0, 0.0);
    aos::Object *satellite = aos::circle(satellite_radius, 360, 0.0, 0.0);

    aos::GravityWell gw(planet); 

    std::vector< double > thetas = { 
        0.0,               M_PI / 4.0,         M_PI / 2.0, 
        3.0 * M_PI / 4.0,  M_PI,               5.0 * M_PI / 4.0,
        3.0 * M_PI / 2.0,  7.0 * M_PI / 4.0,   2.0 * M_PI
    };
    double distance = planet_radius + satellite_radius + 10;

    std::vector< std::vector< double > > expected_positions = { 
        {21.000, 0.000},    {14.849, 14.849},   {0.000, 21.000},
        {-14.849, 14.849},  {-21.000, 0.000},   {-14.849, -14.849},
        {0.000, -21.000},   {14.849, -14.849},  {21.00, 0.0}
    };
    
    for(int i = 0; i < thetas.size(); i++)
    {
        std::vector< double > ep = expected_positions[i];
        double theta = thetas[i];  
        
        std::vector< double > cp = gw.position_to_celestial_body(distance, theta); // Get the calculated position. 

        BOOST_CHECK_MESSAGE( 
            (std::abs(cp[0] - ep[0]) <= 0.01) && (std::abs(cp[0] - ep[0]) <= 0.01),
            "Expected (" << ep[0] << ", " << ep[1] << ") but got (" 
                         << cp[0] << ", " << cp[1] << ") with theta at " << theta << "."
        );
    };
}

BOOST_AUTO_TEST_CASE(OrbitalVelocity)
{
    //aos::Object *planet = aos::circle(100, 360, 0, 0);
    //aos::Object *satellite = aos::circle(1, 360, 0, 0);
    //aos::GravityWell gw(planet);

    //gw->push_back_orbit(
}

BOOST_AUTO_TEST_SUITE_END()

//BOOST_AUTO_TEST_SUITE(Maths)
// 
//BOOST_AUTO_TEST_CASE(universeInOrder)
//{
//    BOOST_CHECK(add(2, 2) == 4);
//}
// 
//BOOST_AUTO_TEST_SUITE_END()
// 
//BOOST_AUTO_TEST_SUITE(Physics)
// 
//BOOST_AUTO_TEST_CASE(specialTheory)
//{
//    int e = 32;
//    int m = 2;
//    int c = 4;
// 
//    BOOST_CHECK(e == m * c * c);
//}
// 
//BOOST_AUTO_TEST_SUITE_END()
