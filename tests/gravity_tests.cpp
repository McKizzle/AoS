#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Gravity
#include <boost/test/unit_test.hpp>

#include <vector>
#include <cmath>

#include <GravityWell.hpp>
#include <utils.hpp>
 
BOOST_AUTO_TEST_SUITE(Gravity)

BOOST_AUTO_TEST_CASE(OrbitalPosition)
{
    double planet_radius = 10;
    double satellite_radius = 1;
    aos::Object *planet = aos::circle(planet_radius, 360, 0.0, 0.0);

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
    double planet_radius = 10;
    double satellite_radius = 1;
    aos::Object *planet = aos::circle(planet_radius, 360, 0.0, 0.0);

    aos::GravityWell gw(planet); 

    std::vector< double > thetas = { 
        0.0,               M_PI / 4.0,         M_PI / 2.0, 
        3.0 * M_PI / 4.0,  M_PI,               5.0 * M_PI / 4.0,
        3.0 * M_PI / 2.0,  7.0 * M_PI / 4.0,   2.0 * M_PI
    };
    double distance = planet_radius + satellite_radius + 10; // 41
    
    for(unsigned int i = 0; i < thetas.size(); i++)
    { 
        // Calculate teh expected velocities. 
        double theta = thetas[i] + (M_PI / 2.0);
        double v_orbital = std::sqrt((GW_GM * (planet->mass)) / (distance + gw.epsilon)) * 0.70;
        std::vector< double > ev = {v_orbital * std::cos(theta), v_orbital * std::sin(theta)};
  
        // Calculate the acutal velocities. 
        theta = thetas[i];  
        std::vector< double > cv = gw.distance_for_orbital_velocity(distance, theta, 0.0); // Get the calculated velocity

        BOOST_CHECK_MESSAGE(
            (std::abs(cv[0] - ev[0]) <= 0.01) && (std::abs(cv[1] - ev[1]) <= 0.01), 
            "Expected a velocity of (" << ev[0] << ", " << ev[1] << " got a velocity of (" << cv[0] << ", " << cv[1] << ") at a distance and position of " << distance << " units and " << theta << " radians.");
    }
}

BOOST_AUTO_TEST_SUITE_END()

