#ifndef _MAIN
//Logging
void logSDLError(std::ostream &os, const std::string &msg);     //Log SDL errors to screen

//Texture Loaders
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren); //Get SDL_Texture from image file. 

//Texture Rendering Functions.
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h); //Render a texture
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr);

//Text Rendering Functions.
SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);
#endif
