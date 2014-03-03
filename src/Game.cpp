#include "includes.hpp"
#include "Game.hpp"

using namespace aos;

Game::Game() 
{
    std::cout << "Created a game object\n"; 
}

Game::~Game()
{
    SDL_GL_DeleteContext(sdl_gl_context);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();    
    std::cout << "Destroyed a game object\n";  
} 

Uint32 Game::main_loop() 
{
    Uint32 dt = 16;
    Uint32 fstart, ftime;
    while(!this->exit)
    {
        fstart = SDL_GetTicks();
        this->render(0, this);
        ftime = SDL_GetTicks() - fstart;
        if(ftime < dt) 
        {
            SDL_Delay((int)(dt - ftime));
        }
    }
    //SDL_Event event;
    //while (SDL_PollEvent(&event))
    //{
    //    switch (event.type)
    //    {
    //        case SDL_USEREVENT:
    //        {   
    //            std::cout << "Caught SDL_USEREVENT" << std::endl;
    //            break;
    //        }
    //            
    //    }

    //}

    return 0;
}

int Game::init() 
{
    std::cout << "Initializing the environment for the game. \n";

    // 1) Load the required data
    //          In this case create a simple object that spins.
     
    // 2) Initialize the game data.
    if(init_sdl() != 0) 
    {
        this->logSDLError(std::cout, "init_sdl(): ");
    }
    if(init_gl() != 0)
    {
       this->logSDLError(std::cout, "init_gl(): "); 
    }

    //std::cout << "Starting SDL_Timer" << std::endl; 
    //std::cout << "Ticks: " << this->ticks << std::endl; 
    //std::cout << "Ticks: " << this->ticks << std::endl; 
    //std::cout << "Done starting SDL_Timer" << std::endl; 

    // Start the main loop
    //Uint32 s_main_loop = main_loop(0, this);

    // 3) TODO: Start the update loop.
    this->game_timer = SDL_AddTimer(16, Game::update_loop, this); 
    // 4) TODO: Start the input loop.
    this->input_timer = SDL_AddTimer(16, Game::input_loop, this);

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
    //SDL_GL_MakeCurrent(game_ptr->sdl_window, game_ptr->sdl_gl_context); // Needed since this is running in its own thread.
    //Clear to red background. 
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
    std::cout << "Game Loop\n";
    SDL_Event event;
    SDL_UserEvent uevent;
    
    uevent.type = SDL_USEREVENT;
    uevent.code = 0;

    event.type = SDL_USEREVENT;
    event.user = uevent;

    Game *aos_game_ptr = (Game * )param;
    std::cout << "Tick: " << aos_game_ptr->ticks << "\nInterval: " << interval << std::endl;
    
    aos_game_ptr->ticks++;
    if(aos_game_ptr->ticks >= 1000)
    {
        std::cout << "Reached maximum ticks. Disableing timer" << std::endl;
        interval = 0;
        aos_game_ptr->exit = true; 
    }
    
    if(aos_game_ptr->exit)
    {
        interval = 0;
    }
    SDL_PushEvent(&event);
    return interval;
}

Uint32 Game::input_loop(Uint32 interval, void * param)
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
