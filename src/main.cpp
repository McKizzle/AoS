/// \file main.cpp Parses arguments and initializes all of the game components. It essentially
///     bootstraps the game into a running state. Besides runing the game main.cpp will be used to 
///     run test cases and make sure the code runs optimally. 
#include "includes.hpp"
#include "Physics.hpp"

using namespace aos;

///
/// \brief Gulps in parameters and initilizes AoS
/// 
/// Simply takes in parameters and calls the proper functions to initialize the game. 
/// 
/// \param[in] argc The number of arguments. 
/// \param[in,out] argv The arguments passed in. 
int main(int argc, char *argv[]) {
    std::cout << "Hello World!" << std::endl;
    Integrator *phgn = new PhysicsGine();
    phgn->integrate();
    phgn->overrided();
    delete phgn;
}




