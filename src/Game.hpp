#ifndef GAME_HPP
#define GAME_HPP
#include "includes.hpp"
#include "Physics.hpp"
//#include "Renderer

namespace aos {
    /// \class Game game.hpp
    /// 
    /// Contains all of the code nessesary to control the game loops. 
    /// There will be three main loops. The integrator loop (updates object positions),
    /// the render loop (draws the objects to the screen), and the input loop (scans for user input).
    /// All three loops will access the objects in the game and update them approprietly. 
    class Game {
        public:
            Game(Integrator * integrator/*, Renderer * renderer, Input * inputer*/);
            ~Game();
        private:
            //Integrator * integrator;
            //Renderer    renderer;
            //Input       inputer;
    };

    /// \class Input input.hpp
    class Input {
        public:
            Input();
            ~Input();
        private:
            ///int input_handler =
            
    };
}
#endif
