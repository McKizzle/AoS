#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE System
#include <boost/test/unit_test.hpp>

#include <vector>
#include <cmath>

#define _USE_MATH_DEFINES

#include <Object.hpp>
#include <System.hpp>
#include <utils.hpp>
 
BOOST_AUTO_TEST_SUITE(Systems)

void delete_objects_from_vector(std::vector< aos::Object *> * objects)
{ 
    while(!objects->empty()) 
    {
        aos::Object *obj = objects->back();
        objects->pop_back();
        delete obj;
    }
}

BOOST_AUTO_TEST_CASE(SystemAddToSystems)
{
    // Test adding System objects to the Systems object.  
    std::vector< aos::Object * > *asteroids = aos::seed_for_asteroids(1234, 50, 3.0, 3.0, 10.0, 10.0, 10.0);

    aos::Systems test_system;
     
    for(std::vector< aos::Object *>::iterator it = asteroids->begin(); it != asteroids->end(); ++it)
    {
        BOOST_CHECK_MESSAGE(test_system.push_back((*it)) != 0, "A Systems object should never return zero!");
    }

    BOOST_CHECK_MESSAGE(test_system.children.size() == asteroids->size(), "Failed to push an object into the system");
        
    delete_objects_from_vector(asteroids);
    delete asteroids;
}

BOOST_AUTO_TEST_CASE(SystemEraseFromSystems)
{
    // Test adding System objects to the Systems object.  
    std::vector< aos::Object * > *asteroids = aos::seed_for_asteroids(1234, 100, 3.0, 3.0, 10.0, 10.0, 10.0);

    aos::Systems test_system;
    std::vector< unsigned int > sys_ids;
    for(std::vector< aos::Object *>::iterator it = asteroids->begin(); it != asteroids->end(); ++it)
    {
        sys_ids.push_back(test_system.push_back((*it)));
    } 

    BOOST_CHECK_MESSAGE(test_system.children.size() == asteroids->size(), "Failed to push an object into the system");

    int count = sys_ids.size();
    for(std::vector< unsigned int >::iterator it = sys_ids.begin(); it != sys_ids.end(); ++it)
    {
        aos::System * erased = test_system.erase((*it));
        count--; 
        BOOST_CHECK_MESSAGE(count == test_system.children.size(), "The number of children should be " << count << ". Instead it is " << test_system.children.size());
    } 

    BOOST_CHECK_MESSAGE(test_system.erase(0) == nullptr, "An empty system needs to return a nullptr");


    delete_objects_from_vector(asteroids);
    delete asteroids;
}



BOOST_AUTO_TEST_SUITE_END()


