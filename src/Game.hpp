//SDL Includes
#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <OpenGL/GL.h>
#elif __linux__
#include <GL/gl.h>
#endif

#ifndef GAME_HPP
#define GAME_HPP
#include "includes.hpp"

namespace aos {
    /// \class Game Game.hpp
    /// \brief Game management area.
    /// 
    /// Contains all of the code nessesary to control the game loops. 
    /// There will be three main loops. The integrator loop (updates object positions),
    /// the render loop (draws the objects to the screen), and the input loop (scans for user input).
    /// All three loops will access the objects in the game and update them approprietly. 
    class Game {
        public:
            Game();
            ~Game();
            /// The init method calls all of the necessary code in order to setup 
            ///  the game environment. If it fails to do so, then it will provide 
            ///  an error code.
            /// \return 0 on success otherwise return another number.
            int init(); 
        private:
            int screen_width = 512, screen_height = 512;
            SDL_Window * sdl_window;
            SDL_GLContext sdl_gl_context;
            /// The render_loop runs in a thread. Its sole job is to call
            ///  a renderable object.
            void render_loop();
            /// The update_loop runs in a thread. Its sole job is to call
            ///  an updatable object.
            void update_loop();
            int init_gl();      ///< Initializes OpenGL for the game.
            int init_sdl();     ///< Initializes SDL for the game.
    };
}
#endif
