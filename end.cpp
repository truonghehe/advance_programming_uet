#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "my_class.h"
#include <iostream>
bool check (int x , int y , int box_x , int box_y , int box_w , int box_h)
{
    bool temp= false;
    if ( x >= box_x - box_w/2 && x <= box_x + box_w/2 && y >= box_y - box_h/2 && y <= box_y + box_h/2 ) temp = true;
    else temp = false;
    return temp;
}
void light_up_green(SDL_Renderer* renderer, texture box , int x , int y , int box_x , int box_y )
{
    int box_w = 189 , box_h = 78;
    if (check(x, y , box_x , box_y , box_w , box_h ) )
    {
        box.loadtexture(renderer, "/Users/chuongdz/Desktop/golf/stuff/green_box_lighted.png");
        box.render(renderer , box_x - box.getW()/2 , box_y - box.getH()/2);
    } 
    else
    {
        box.loadtexture(renderer, "/Users/chuongdz/Desktop/golf/stuff/green_box.png");
        box.render(renderer, box_x - box.getW()/2 , box_y - box.getH()/2);
    } 
}
void light_up_white(SDL_Renderer* renderer, texture box , int x , int y , int box_x , int box_y )
{
    int box_w = 200 , box_h = 95 ;
    if (check(x, y , box_x , box_y, box_w , box_h ) )
    {
        box.loadtexture(renderer, "/Users/chuongdz/Desktop/golf/stuff/white_box_lighted.png");
        box.render(renderer , box_x - box.getW()/2 , box_y - box.getH()/2);
    } 
    else
    {
        box.loadtexture(renderer, "/Users/chuongdz/Desktop/golf/stuff/white_box.png");
        box.render(renderer, box_x - box.getW()/2 , box_y - box.getH()/2);
    } 
}
void start ( int & state , int x, int y , int box_x , int box_y )
{
    int box_w = 200 , box_h = 95 ;
    if ( check(x , y , box_x , box_y , box_w , box_h ))
    {
        state = 2;
    } 
}
void restart( int& level , int& strokes, int& state, int x , int y, int box_x , int box_y)
{
    int box_w = 189 , box_h = 78;
    if( check(x , y , box_x , box_y , box_w , box_h) ) 
    {
        level = 1; 
        strokes = 0;
        state = 2;
    }
}
void endgame(int x , int y , int box_x , int box_y, bool &quit )
{
    int box_w = 189 , box_h = 78;
    if (check(x , y ,box_x , box_y , box_w , box_h )) quit = true;
}
