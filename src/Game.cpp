#include "Game.hpp"

namespace aos
{

Game::Game(){}

Game::~Game()
{   
    delete gameverse;

    SDL_GL_DeleteContext(sdl_gl_context);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();    
} 

Uint32 Game::main_loop() 
{
    Uint32 fstart, ftime;
    while(!this->exit)
    {
        fstart = SDL_GetTicks();
        this->render(dt, this);
        this->input_handler(dt, this);
        ftime = SDL_GetTicks() - fstart;
        
        if(ftime < dt) 
        {
            SDL_Delay((int)(dt - ftime));
        }
        else { if(ftime > dt) 
        {
            dt = max_dt;
        }
        else 
        {
            dt = ftime;
        }}
    }

    return 1;
}

int Game::start_game()
{
    // Start the update thread
    this->update_thread = new std::thread(Game::update_loop, 16, this);
    this->main_loop();

    return 0;
}

int Game::init() 
{
    // Initialize SDL and openGL
    if(init_sdl() != 0) 
    {
        this->logSDLError(std::cout, "init_sdl(): ");
    }
    if(init_gl() != 0)
    {
       this->logSDLError(std::cout, "init_gl(): "); 
    }
    
    switch(this->game_mode)
    {
        case 0:
            this->gameverse = single_asteroid(); break;
        case 1:
            this->gameverse = bunch_of_rocks(); break;
        case 2:
            this->gameverse = one_planet(); break;
        case 3:
            this->gameverse = two_planets(); break;
        default:
            this->gameverse = two_planets(); break;
        
    }
    
    return 1;
}

int Game::init_sdl() 
{
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0)
    {
        return 1;
    } 

    sdl_window = SDL_CreateWindow(
            "Asteroids on Steroids",
            10, 10, 
            screen_width, screen_height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if( this->sdl_window == nullptr ) 
    {
        return 2;
    }

    return 0;
}

int Game::init_gl()
{ 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2); // Request openGL 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Set up double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Set the color depth. 

    // 3) Create an SDL opengl Context.
    sdl_gl_context = SDL_GL_CreateContext(sdl_window);
    if(sdl_gl_context == nullptr) 
    { 
        std::cout << SDL_GetError() << std::endl;
        std::cout << "Quitting AoS" << std::endl;
        std::exit(0);
    } 
    else
    {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }
    
    
    int setcurrent_result = SDL_GL_MakeCurrent(sdl_window, sdl_gl_context);
    //SDL_GL_SetSwapInterval(1); // Enable V-Sync
    
    glViewport(0, 0, screen_width, screen_height);
    print_glError("GL Viewport");
    glMatrixMode(GL_PROJECTION);
    print_glError("Matrix Mode");
    glLoadIdentity();
    print_glError("Load Identity");
    GLfloat aspect = (GLfloat)screen_width / (GLfloat)screen_height;
    //gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    //print_glError("Ortho 2D");
    glOrtho(-glortho_width * aspect, glortho_width * aspect, -glortho_height, glortho_height, -1.0, 1.0);
    print_glError("Ortho");
    glMatrixMode(GL_MODELVIEW);

    return 0;
}

Uint32 Game::render(Uint32 interval, void *param)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    gameverse->render(interval, this->ticks);
    glFlush();
    SDL_GL_SwapWindow(this->sdl_window);

    return interval;
}

Uint32 Game::update_loop(Uint32 interval, void * param)
{
    Uint32 fstart, ftime;
    Game *aos_game_ptr = (Game * )param; 
    Uint32 min_dt = aos_game_ptr->min_dt;
    Uint32 max_dt = aos_game_ptr->max_dt;
    Uint32 dt; 
    while(!aos_game_ptr->exit)
    {
        dt = aos_game_ptr->dt;
        fstart = SDL_GetTicks();
        
        aos_game_ptr->gameverse->update(dt, aos_game_ptr->ticks);
        
        ftime = SDL_GetTicks() - fstart;
        aos_game_ptr->ticks++;
        
        
        // Allow a variable dt between the minimum and maximum dt specified in 
        // the game class.
        if(ftime < min_dt) // Only sleep if execution time takes less than dt.
        {  
            aos_game_ptr->dt = min_dt;

            std::chrono::milliseconds stime(dt - ftime);
            std::this_thread::sleep_for(stime);
        } 
        else { if(ftime > max_dt) {
            aos_game_ptr->dt = max_dt;
                    
        }
        else 
        { 
            aos_game_ptr->dt = ftime;
        }}

    }

    return interval;
}

Uint32 Game::input_handler(Uint32 interval, void * param)
{
    Game * game_ptr = (Game *) param;

    SDL_Event event;


    // Get all of the keyboard events.
    const Uint8* currKeyStates = SDL_GetKeyboardState(NULL);
    this->gameverse->send_event(currKeyStates, interval, game_ptr->ticks);

    while(SDL_PollEvent(&event)) 
    {   
        switch(event.type) 
        {
            case SDL_QUIT:
                game_ptr->exit = true;
                interval = 0;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) 
                {
                    game_ptr->exit = true;
                    interval = 0;
                }
                else 
                {    
                }
                break;
            default:
                break;
        }
    }

    return interval;
}

void Game::logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

void Game::print_glError(const std::string &extra)
{
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        std::cout << extra << " -- GL Error: " << gluErrorString(error) << std::endl;
    }
}

} // END namespace aos
