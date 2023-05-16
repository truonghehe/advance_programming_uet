#pragma once
void light_up_green(SDL_Renderer* renderer, texture box , int x , int y , int box_x , int box_y );
void light_up_white(SDL_Renderer* renderer, texture box , int x , int y , int box_x , int box_y );
void start ( int & state , int x, int y , int box_x , int box_y );
void restart( int& level , int& strokes, int& state, int x , int y, int box_x , int box_y);
void endgame (int x , int y , int box_x , int box_y, bool& quit );