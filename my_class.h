#pragma once
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
class texture
{
    public:
        texture();
        ~texture();
        void loadtexture(SDL_Renderer* renderer, std:: string path);
        void free();
        void loadtext(SDL_Renderer* renderer,TTF_Font* font , std:: string text , SDL_Color textcolor);
        void loadnumber(SDL_Renderer* renderer, TTF_Font* font , int num, std::string text , SDL_Color numcolor);
        void render(SDL_Renderer* renderer,int x , int y );
        void render_rotate(SDL_Renderer* renderer,int x , int y , SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip);
        void render1tile(SDL_Renderer* renderer, int x , int y);
        int getW();
        int getH();
    private:
        SDL_Texture* Ctexture;
        int width;
        int height;
};