#include <SDL2/SDL.h>
#include <iostream>
const int SCREEN_WIDTH = 420;
const int SCREEN_HEIGHT = 630;
const int tile = 42;
const int ball_w = 16;
const int ball_h = 16;
const int hole_w = 16;
const int hole_h = 19;
const int hole_x = SCREEN_WIDTH/2 - hole_w/2;
const int hole_y =tile*3 - hole_h/2;
void check_wall_collision( double x  , double y , double &vel_x , double &vel_y , double& real_vel_x , double& real_vel_y )
{
    if ( x + ball_w + real_vel_x > SCREEN_WIDTH )
    {
        vel_x = -vel_x;
        real_vel_x = -real_vel_x;
    }
    if ( y + ball_h + real_vel_y > SCREEN_HEIGHT) 
    {
        vel_y = -vel_y;
        real_vel_y = -real_vel_y;
    }
    if ( x + vel_x < 0)
    {
        vel_x = -vel_x;
        real_vel_x = -real_vel_x;
    }
    if ( y + vel_y < 0) 
    {
        vel_y = -vel_y;
        real_vel_y = -real_vel_y;
    }
}
double velocity_and_time( double vel_d , double portion)
{   
    double real_vel = vel_d - vel_d*portion/100;
    if ( real_vel > 20 ) real_vel = 20;
    if ( real_vel < -20 ) real_vel = 20;
    if (abs(real_vel) <= 0.001 ) return 0;
    else return real_vel;
}
bool check_hole(double x , double y )
{
    if ( hole_x <= x + ball_w/2  && hole_x + hole_w >= x + ball_w/2 && hole_y <= y + ball_h/2 && hole_y + hole_h >= y + ball_h/2 ) return true;
    else return false;
}
void check_block_collision(double ball_x, double ball_y, double& vel_x , double& vel_y, double& real_vel_x , double& real_vel_y , int x , int y)
{
    //side
    if(ball_x + ball_w + vel_x >= x && ball_x + vel_x <= x + tile && ball_y >= y && ball_y  <= y + tile) {real_vel_x = -real_vel_x; vel_x = -vel_x;}
    //front
    if(ball_x >= x && ball_x <= x + tile && ball_y + ball_h + vel_y >= y && ball_y + vel_y <= y + tile) {real_vel_y = - real_vel_y ; vel_y = -vel_y;}
}