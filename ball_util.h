#ifndef COLLIDE_H
#define COLLIDE_H
void check_wall_collision( double x  , double y , double &vel_x , double &vel_y , double &real_vel_x , double &real_vel_y );
double velocity_and_time( double vel_d , double portion);
bool check_hole(double x , double y);
void check_block_collision(double ball_x, double ball_y, double& vel_x , double& vel_y, double &real_vel_x , double &real_vel_y , int x , int y);
#endif