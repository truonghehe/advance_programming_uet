#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "my_class.h"
#include "end.h"

void renderbackground(SDL_Renderer* renderer)
{
    SDL_Texture* background = nullptr;
    SDL_Surface* temp = IMG_Load("/Users/chuongdz/Desktop/golf/stuff/playground.png");
    background = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    SDL_RenderCopy(renderer , background , NULL , NULL);
}
void render_overlay(SDL_Renderer* renderer)
{
    SDL_Texture* overlay = nullptr;
    SDL_Surface* temp = IMG_Load("/Users/chuongdz/Desktop/golf/stuff/endscreen_overlay.PNG");
    overlay = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    SDL_RenderCopy(renderer , overlay , NULL , NULL);
}

void render_endscreen(SDL_Renderer* renderer)
{
    renderbackground(renderer);
    render_overlay(renderer);
    
}