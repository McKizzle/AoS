/// \file main.cpp Parses arguments and initializes all of the game components. It essentially
///     bootstraps the game into a running state. Besides runing the game main.cpp will be used to 
///     run test cases and make sure the code runs optimally. 
#include "includes.hpp"
#include "Physics.hpp"
#include "Object.hpp"
#include "Game.hpp"

#include <getopt.h>

using namespace aos;

///
/// \brief Gulps in parameters and initilizes AoS
/// 
/// Simply takes in parameters and calls the proper functions to initialize the game. 
/// 
/// \param[in] argc The number of arguments. 
/// \param[in,out] argv The arguments passed in. 
int main(int argc, char *argv[]) {
    // First parse the arguments.
    const struct option longopts[] {
        // name,         has_arg,            flag, val
        {"help",         no_argument,        0,    'h'}, //help will print the version. 
        {"width",        optional_argument,  0,    'x'},
        {"height",       optional_argument,  0,    'y'}, 
        {"frame-rate",   optional_argument,  0,    'r'}, //update every miliseconds. 
        {"aspect-ratio", optional_argument,  0,    'a'}, // the aspect ratio of the screen. 4:3, 16:9, 16:10
        {0,              0,                  0,     0 }
    };
    
    int longopts_index = 0;
    int iarg = 0;
    while((iarg = getopt_long(argc, argv, "", longopts, &longopts_index)) != -1) 
    {
        std::cout << "Printing the option" << std::endl;
        std::cout << std::string((char *)&iarg) << std::endl;
        std::cout << "Printing the value" << std::endl;
        std::cout << optarg << std::endl;

        switch(iarg) 
        {
            case 'h':
                std::cout << "Printing help text to the screen\n";
                break;
            case 'x':
                std::cout << "The width has been set\n";
                break;
            case 'y':
                std::cout << "The height has been set\n";
                break;
            case 'r':
                std::cout << "The refresh rate has been set\n";
                break;
            case 'a':
                std::cout << "The aspect ratio has been set\n";
                break;
        }
    }

    // Now Initialize the game. 
    // Create a Game object. 
    // Create an Integrator.
    // Create a Renderer.
    // Create a InputGrabber.
    
    // Start the Game Object. 
}




