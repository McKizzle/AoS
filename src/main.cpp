#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// OS Specific includes
#ifdef __APPLE__ 
#include <SDL2/SDL_ttf.h> 
#include <OpenGL/GL.h> 
#elif __linux
#include <GL/gl.h>
#include <SDL/SDL_ttf.h>
#endif

#include "main.h"

/**
 * Log an SDL error with some error message to the output stream of our choice
 * @param os: The output stream to write the message too.
 * @param msg: The error message to write, format will be "msg error: SDL_GetError()
 */
void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
 * Main Function!! :P
 * 1) Create an SDL_Window
 * 2) Create an SDL_GLContext
 * 3) Request for an opengl context (in this case we'll be usng 3.2
 * 4) Enable double buffering with a depth of 32bits
 * 5) 
 */
int main(int argc, char **argv)
{
    int screen_width = 512, screen_height = 512;

    SDL_Window *win;
    SDL_GLContext glcontext; 

    //Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }  

    // Request opengl 3.2 context. 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

    //Enable double buffering.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Now we can display a window with the texture. 
    win = SDL_CreateWindow("Lesson 7 OpenGL", 100, 100, screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        logSDLError(std::cout, "CreateWindow");
        return 2; //What error does returning a 2 symbolize?
    }
    //checkSDLError(__LINE__);

    //Create the openGL context and attach it to the window.
    glcontext = SDL_GL_CreateContext(win);
    //checkSDLError(__LINE__);

    //Syncronize buffer swaps with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);
    
    //Clear to red background. 
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(win);
    SDL_Delay(2000);

    glClearColor(0.0, 1.0, 1.0 , 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(win);
    SDL_Delay(2000);
    

    glClearColor(0.0, 0.0, 1.0 , 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(win);
    SDL_Delay(2000);

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(win);
    SDL_Quit();    
    return 0;
}


