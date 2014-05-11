/// \file main.cpp Parses arguments and initializes all of the game components. It essentially
///     bootstraps the game into a running state. Besides runing the game main.cpp will be used to 
///     run test cases and make sure the code runs optimally. 
#include "Object.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Ode.hpp"

#include <getopt.h> 
#include <GL/glut.h>

using namespace aos;

///
/// Takes in an optarg (char pointer) and converts it into an 
/// integer.
/// 
/// \param[in] optarg The optarg char * from getopt.h
/// \returns an integer representation of the optarg value.
int optarg_to_int(char * optarg) {
    std::string *tmp = new std::string(optarg);
    int width = std::stoi(*tmp);
    delete tmp;
    return width;
}

///
/// \brief Gulps in parameters and initilizes AoS
/// 
/// Simply takes in parameters and calls the proper functions to initialize the game. 
/// 
/// \param[in] argc The number of arguments. 
/// \param[in,out] argv The arguments passed in. 
int main(int argc, char *argv[]) {  
    glutInit(&argc, argv); // To render text. TODO: REMOVE HACK!

    bool DEBUG = false;

    const struct option longopts[] { ///< Define the program's long arguments for getopt.h
        // name,         has_arg,            flag, val
        {"help",         no_argument,        0,    'h'}, 
        {"debug",        no_argument,        0,    'd'},
        {"width",        optional_argument,  0,    'x'},
        {"height",       optional_argument,  0,    'y'}, 
        {"frame-rate",   optional_argument,  0,    'r'}, 
        {"aspect-ratio", optional_argument,  0,    'a'}, 
        {"mode",         optional_argument,  0,    'm'},
        {0,              0,                  0,     0 }
    };
    const char * shortopts = "hdx:y:r:a:"; ///< Define the program's short arguments for getopt.h

    std::string * aspect_ratio = new std::string("4:3"); 
    int mode = 0;
    //int width = 1600, height = 1000, refresh_rate = 60;
    int width = 1152, height = 720, refresh_rate = 60;
    //int width = 800, height = 600, refresh_rate = 60;
    
    // Extract program arguments.
    int longopts_index = 0;
    int iarg = 0;
    while((iarg = getopt_long(argc, argv, shortopts, longopts, &longopts_index)) != -1) 
    {
        switch(iarg) 
        {
            case 'h':
                std::cout << "Printing help text to the screen\n";
                return 1;
                break;
            case 'd':
                DEBUG = true;
            case 'x':
                if(optarg != 0) {
                    width = optarg_to_int(optarg);
                } 
                break;
            case 'y':
                if(optarg != 0) 
                    height = optarg_to_int(optarg); 
                break;
            case 'r':
                if(optarg != 0)
                    refresh_rate = optarg_to_int(optarg); 
                break;
            case 'a':
                if(optarg != 0) {
                    delete aspect_ratio; 
                    aspect_ratio = new std::string(optarg); 
                }
                break;
            case 'm':
                if(optarg != 0) {
                    mode = optarg_to_int(optarg);
                }
        }
    }
          
    if(DEBUG) 
    {
        std::cout << "Width: " << width << std::endl; 
        std::cout << "Height: " << height << std::endl;     
        std::cout << "Refresh Rate: " << refresh_rate << std::endl;
        std::cout << "Aspect Ratio: " << *aspect_ratio << std::endl;
    }

    // Now Initialize the game.
    // Create a Game object.
    Game *aos_game = new Game();
    aos_game->screen_width = width;
    aos_game->screen_height = height;
    aos_game->glortho_width = 40; //40 before.
    aos_game->glortho_height = 40;

    aos_game->game_mode = mode;
    aos_game->init();
    int res = aos_game->start_game();
    
    delete aspect_ratio;
    delete aos_game;

    return res;
}






