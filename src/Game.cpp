#include "includes.hpp"
#include "Game.hpp"

using namespace aos;

Game::Game() 
{
    std::cout << "Created a game object\n"; 
}

Game::~Game()
{
    std::cout << "Destroyed a game object\n";  
}

int Game::init() 
{
    std::cout << "Initializing the environment for the game. \n";

    // 1) Load the required data
    //          In this case create a simple object that spins.
     
    // 2) Initialize the game data.
    init_sdl();
    init_gl();

    // 3) TODO: Start the update loop.
    render_loop();
    // 4) TODO: Start the render loop.
    update_loop();

    return 1;
}

int Game::init_sdl() 
{
    if( SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        // Failed to initizlize SDL
        return 1;
    } 

    sdl_window = SDL_CreateWindow(
            "Asteroids on Steroids",
            100, 100, 
            screen_width, screen_height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if( this->sdl_window == nullptr ) 
    {
        return 2;
    }

    return 1;
}


int Game::init_gl()
{ 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Request openGL 3
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Set up double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Set the color depth. 

    // 3) Create an opengl Context.
    sdl_gl_context = SDL_GL_CreateContext(sdl_window);

    SDL_GL_SetSwapInterval(1); // Enable V-Sync

    return 0;
}

void Game::render_loop()
{ 
    //Clear to red background. 
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(sdl_window);
    SDL_Delay(2000);

    glClearColor(0.0, 1.0, 1.0 , 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(sdl_window);
    SDL_Delay(2000);
    

    glClearColor(0.0, 0.0, 1.0 , 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(sdl_window);
    SDL_Delay(2000);

    SDL_GL_DeleteContext(sdl_gl_context);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();    
}

void Game::update_loop()
{

}
