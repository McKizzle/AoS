//SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_timer.h>
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
            bool exit = false;
            void logSDLError(std::ostream &os, const std::string &msg);
            Uint32 screen_width = 512, screen_height = 512;
            Game();
            ~Game();
            /// The init method calls all of the necessary code in order to setup 
            ///  the game environment. If it fails to do so, then it will provide 
            ///  an error code.
            /// \return 0 on success otherwise return another number.
            int init(); 
        private:
            SDL_Window * sdl_window;
            SDL_GLContext sdl_gl_context;
            Uint32 ticks = 0;
            SDL_TimerID game_timer;
            std::thread * update_thread;
            /// The main game loop. Compliant to the SDL_AddTimer function.
            Uint32 main_loop();
            /// The render is planned to run in a thread. For now it 
            /// will be ran in the main_loop. Its sole job is to call
            ///  a renderable object.
            Uint32 render(Uint32 interval, void *param);
            /// The update_loop is planned to run in a thread. Its sole job is to call
            ///  an updatable object.
            static Uint32 update_loop(Uint32 interval, void * param);
            /// The input_loop runs in its own thread and handles events from the user.
            Uint32 input_handler(Uint32 interval, void * param);
            int init_gl();      ///< Initializes OpenGL for the game.
            int init_sdl();     ///< Initializes SDL for the game.
    };
}
#endif
