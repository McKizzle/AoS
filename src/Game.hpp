#ifdef __APPLE__
#include <OpenGL/GL.h>
#elif __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <thread>
#include <mutex>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_timer.h>

#ifndef GAME_HPP
#define GAME_HPP

#include "Object.hpp"
#include "Player.hpp"
#include "utils.hpp"
#include "Camera.hpp"
#include "Grid.hpp"
#include "Collision.hpp"
#include "GravityWell.hpp"
#include "Systems.hpp"
#include "Planet.hpp"
//#include "AsteroidsOnSteroids.hpp"

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
            Uint32 screen_width = 512;
            Uint32 screen_height = 512;
            GLfloat glortho_width = 20.0;
            GLfloat glortho_height = 20.0;
            Uint32 ticks = 0;
            Uint32 min_dt = 8; 
            Uint32 max_dt = 16; 
            Uint32 dt = min_dt; ///< Timestep in miliseconds. Default to minimum dt.
            SDL_Window * sdl_window; ///< The SDL window to display the OpenGL Context
            SDL_GLContext sdl_gl_context; ///< The OpenGL context to render the game. Using the SDL version allows usage of SDL 2d libraries.
            std::thread * update_thread; ///< Updates the game. 
            Systems *gameverse; ///< The game system goes here. 
            Camera *camera = nullptr;

            int game_mode = 0; /// TODO: This is a temporary variable to handle start mode of the game.

            Game();
            ~Game();
            /// The init method calls all of the necessary code in order to setup 
            ///  the game environment. If it fails to do so, then it will provide 
            ///  an error code.
            /// \return 0 on success otherwise return another number.
            int init(); 
            int init_gl();      ///< Initializes OpenGL for the game.
            int init_sdl();     ///< Initializes SDL for the game.
            int start_game();   ///< Starts up all of the necessary threads. 
            
            
            /// Log sdl errors to the desired output stream.
            void logSDLError(std::ostream &os, const std::string &msg);
            void print_glError(const std::string &extra);
        //private:

            /// The main game loop. Runs in the main thread.
            Uint32 main_loop();

            /// The render is planned to run in a thread. For now it 
            /// will be ran in the main_loop. Its sole job is to call
            ///  a renderable object.
            /// @param [in] interval TODO: Remove this argument. It's useless. 
            /// @param [in, out] param aditional parameters that the update procedure may need. 
            ///     TODO: Change the the type of param to Game*
            Uint32 render(Uint32 interval, void *param);

            /// The input_handler is called by the main_loop function. The 
            ///     design of SDL doesn't allow events to be handled in a seperate thread.
            /// @param [in] interval TODO: Remove this argument. It's useless. 
            /// @param [in, out] param aditional parameters that the update procedure may need. 
            ///     TODO: Change the the type of param to Game*
            /// 
            /// \return The return value is to be determined for now return a Uint32. 
            Uint32 input_handler(Uint32 interval, void * param);

            /// The update_loop is planned to run in a thread. Its sole job is to call
            ///  an updatable object.
            /// @param [in] interval TODO: Remove this argument. It's useless.  
            /// @param [in, out] param aditional parameters that the update procedure may need. 
            ///     TODO: Change the the type of param to Game*
            static Uint32 update_loop(Uint32 interval, void * param);


    };
}
#endif
