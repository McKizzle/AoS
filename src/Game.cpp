#include "includes.hpp"
#include "Game.hpp"

using namespace aos;

Game::Game() {}

Game::~Game()
{ 
    SDL_GL_DeleteContext(sdl_gl_context);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();    
} 

Uint32 Game::main_loop() 
{
    Uint32 dt = 16;
    Uint32 fstart, ftime;
    while(!this->exit)
    {
        fstart = SDL_GetTicks();
        this->render(0, this);
        this->input_handler(0, this);

        ftime = SDL_GetTicks() - fstart;
        if(ftime < dt) 
        {
            SDL_Delay((int)(dt - ftime));
        }
    }

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

    // Create and load the game objects. 
    //float shp_verts[] = {0.0, 1.0, -0.3, -0.3, 0.3, -0.3};
    //float shp_edgs[]  = {0, 1, 1, 2, 2};

    //delete shp_verts;
    //delete shp_edgs;


    // Start the update thread
    //this->game_timer = SDL_AddTimer(16, Game::update_loop, this); 
    this->update_thread = new std::thread(Game::update_loop, 16, this);
    // Start the main loop 
    this->main_loop();

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
            100, 100, 
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Request openGL 3
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Set up double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Set the color depth. 

    // 3) Create an opengl Context.
    sdl_gl_context = SDL_GL_CreateContext(sdl_window);

    SDL_GL_SetSwapInterval(1); // Enable V-Sync

    return 0;
}

Uint32 Game::render(Uint32 interval, void *param)
{ 
    Uint32 ticks = (this->ticks % 30) / 10;
    switch(ticks) 
    {
        case 0: 
            glClearColor(1.0, 0.0, 0.0, 1.0);
            break;
        case 1: 
            glClearColor(0.0, 1.0, 0.0, 1.0);
            break;
        case 2: 
            glClearColor(0.0, 0.0, 1.0, 1.0);
            break;
        default:
            break;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(this->sdl_window);

    return interval;
}

Uint32 Game::update_loop(Uint32 interval, void * param)
{
    //SDL_Event event;
    //SDL_UserEvent uevent;
    //
    //uevent.type = SDL_USEREVENT;
    //uevent.code = 0;

    //event.type = SDL_USEREVENT;
    //event.user = uevent;

    Uint32 dt = 16;
    Uint32 fstart, ftime;
    Game *aos_game_ptr = (Game * )param; 
    while(!aos_game_ptr->exit)
    {
        fstart = SDL_GetTicks();

        ftime = SDL_GetTicks() - fstart;
        aos_game_ptr->ticks++;
        std::chrono::milliseconds stime(dt - ftime);
        std::this_thread::sleep_for(stime);
    }

    return interval;
}

Uint32 Game::input_handler(Uint32 interval, void * param)
{
    Game * game_ptr = (Game *) param;
 
    SDL_Event event;
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
                    // Send the event to an object. 
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
