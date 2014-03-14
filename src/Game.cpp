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
        else { if(ftime > dt) 
        {
            dt = max_dt;
        }
        else 
        {
            dt = ftime;
        }}
    }

    return 0;
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

    // Create the game objects. 
    Object * plyr = Player::default_player();
    objects.push_back(plyr);

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Set up double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Set the color depth. 

    // 3) Create an opengl Context.
    sdl_gl_context = SDL_GL_CreateContext(sdl_window);

    SDL_GL_SetSwapInterval(1); // Enable V-Sync

    //glViewport(0, 0, screen_width, screen_height);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    ////GLfloat aspect = (GLfloat)screen_width / (GLfloat)screen_height;
    ////gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    //glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
    //glMatrixMode(GL_MODELVIEW);

    printf("%s\n", glGetString(GL_VERSION));
    return 0;
}

Uint32 Game::render(Uint32 interval, void *param)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0, 0, -2);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.2, 0.2);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush();
    //glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();
    ////glTranslatef(0.0f, 0.0f, -5.0f);

    //glColor3f(1.0f, 1.0f, 1.0f);
    //glBegin(GL_QUADS); // Start drawing a quad primitive  

    //    glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner  
    //    glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner  
    //    glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner  
    //    glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner  

    //glEnd();  
    ////for(std::vector< Object* >::iterator it = objects.begin(); it != objects.end(); ++it) 
    ////{
    ////    //std::cout << "Calling objects to render" << std::endl;
    ////    Object *rndrf = *it;
    ////    rndrf->render(interval, this->ticks);
    ////}

    //glFlush();
    //SDL_GL_SwapWindow(this->sdl_window);

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

    Uint32 fstart, ftime;
    Game *aos_game_ptr = (Game * )param; 
    Uint32 min_dt = aos_game_ptr->min_dt;
    Uint32 max_dt = aos_game_ptr->max_dt;
    Uint32 dt; 
    while(!aos_game_ptr->exit)
    {
        dt = aos_game_ptr->dt;
        fstart = SDL_GetTicks();

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
                    // Get all of the keyboard events.
                    const Uint8* currKeyStates = SDL_GetKeyboardState(NULL);
                    for(std::vector< Object* >::iterator it = objects.begin(); it != objects.end(); ++it) 
                    {
                        Object *evntf = *it;
                        evntf->send_event(currKeyStates, interval, game_ptr->ticks);
                    }
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
