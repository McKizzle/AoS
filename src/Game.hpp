#ifndef GAME_HPP
#define GAME_HPP
#include "includes.hpp"
#include "Physics.hpp"
//#include "Renderer

namespace aos {
    class Game {
        public:
            Game(Integrator * integrator/*, Renderer * renderer, Input * inputer*/);
            ~Game();
        private:
            Integrator * integrator;
            //Renderer    renderer;
            //Input       inputer;
    };
}
#endif
