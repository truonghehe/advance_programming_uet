#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

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

texture::texture(){}
texture::~texture(){};

void texture::loadtexture(SDL_Renderer* renderer, std::string path)
{
    free();
    SDL_Surface* temp = IMG_Load( path.c_str() );
    Ctexture = SDL_CreateTextureFromSurface(renderer , temp);
    width = temp->w;
    height = temp->h;
    SDL_FreeSurface(temp);
    
}
void texture:: loadtext (SDL_Renderer* renderer, TTF_Font* font , std::string text , SDL_Color textcolor)
{
    free();
    SDL_Surface*temp = TTF_RenderText_Solid(font , text.c_str() , textcolor);
    Ctexture = SDL_CreateTextureFromSurface(renderer , temp);
    width = temp->w;
    height = temp->h;
    SDL_FreeSurface(temp);
}
void texture::loadnumber(SDL_Renderer* renderer, TTF_Font* font , int num, std::string text , SDL_Color numcolor)
{
    free();
    text +=  std::to_string(num);
    SDL_Surface* temp = TTF_RenderText_Solid(font , text.c_str() , numcolor);
    Ctexture = SDL_CreateTextureFromSurface(renderer , temp );
    width = temp->w;
    height = temp->h;
    SDL_FreeSurface(temp);
}
void texture:: free()
{
    if ( Ctexture == NULL || Ctexture == nullptr)
    {
        SDL_DestroyTexture(Ctexture);
        Ctexture = NULL;
        width = 0;
        height = 0;
    }
}
void texture::render(SDL_Renderer* renderer, int x , int y)
{
    SDL_Rect rect = { x , y , width , height };
    SDL_RenderCopy(renderer , Ctexture , NULL , &rect);
}
void texture::render_rotate(SDL_Renderer* renderer, int x , int y , SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip)
{
    SDL_Rect rect = { x , y , width , height };
    if ( clip != NULL )
    {
        rect.w = clip->w;
        rect.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, Ctexture , clip , &rect , angle , center , flip );
}
void texture:: render1tile(SDL_Renderer* renderer, int x , int y)
{
    SDL_Rect rect = { x , y , 42, 42};
    SDL_RenderCopy(renderer , Ctexture , NULL , &rect);
}
int texture::getW()
{
    return width;
}
int texture::getH()
{
    return height;
}