#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <bits/stdc++.h>
#include "background.h"
#include "ball_util.h"
#include "my_class.h"
#include "end.h"

const int SCREEN_WIDTH = 420;
const int SCREEN_HEIGHT = 630;
const int tile = 42;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Color white = {0xff , 0xff , 0xff };
SDL_Color black = {0, 0, 0, 0};
TTF_Font* outter_font = nullptr;
TTF_Font* inner_font = nullptr;
TTF_Font* middle_font = nullptr;

texture ball;
texture hole;
texture wintext;
texture press_anywhere;
texture block_tile;
texture point;
texture stroke_bg;
texture stroke_count;
texture endscreen_overlay;
texture total_stroke;
texture pass_all_level;
texture green_box;
texture play_again;
texture quit_game;
texture logo;
texture white_box;
texture start_game;

Mix_Chunk* goal_sound;
Mix_Chunk* swing;

void init()
{
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    window = SDL_CreateWindow("GOLF" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer (window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor ( renderer , 0xff , 0xff , 0xff , 0xff);
    int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	if( TTF_Init() == -1 ) printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
}
void loadmedia()
{
    outter_font = TTF_OpenFont("/Users/chuongdz/Desktop/golf/stuff/font.ttf" , 80);
    middle_font = TTF_OpenFont("/Users/chuongdz/Desktop/golf/stuff/font.ttf" , 35);
    inner_font = TTF_OpenFont("/Users/chuongdz/Desktop/golf/stuff/font.ttf" , 25);

    ball.loadtexture(renderer,"/Users/chuongdz/Desktop/golf/stuff/ball.png");
    hole.loadtexture(renderer,"/Users/chuongdz/Desktop/golf/stuff/hole.png");
    block_tile.loadtexture(renderer,"/Users/chuongdz/Desktop/golf/stuff/block_tile.png");
    point.loadtexture(renderer,"/Users/chuongdz/Desktop/golf/stuff/point.png");
    stroke_bg.loadtexture(renderer,"/Users/chuongdz/Desktop/golf/stuff/strokes.png");
    endscreen_overlay.loadtexture(renderer, "/Users/chuongdz/Desktop/golf/stuff/endscreen_overlay.PNG");
    logo.loadtexture(renderer , "/Users/chuongdz/Desktop/golf/stuff/logo.png" );
    white_box.loadtexture(renderer, "/Users/chuongdz/Desktop/golf/stuff/white_box.png");

    press_anywhere.loadtext(renderer,inner_font , "(press anywhere to continue)" , white);
    wintext.loadtext(renderer, outter_font , "next level" , white);
    pass_all_level.loadtext(renderer, middle_font , "congrat! you passed all levels", white);
    play_again.loadtext(renderer , middle_font , "play again", white);
    quit_game.loadtext(renderer , middle_font , "quit" , white);
    start_game.loadtext(renderer , middle_font , "start" , black);

    goal_sound = Mix_LoadWAV("/Users/chuongdz/Desktop/golf/audio/goal.mp3");
    swing = Mix_LoadWAV("/Users/chuongdz/Desktop/golf/audio/swing.mp3");
}
void close()
{
    TTF_CloseFont(outter_font);
    TTF_CloseFont(inner_font);
    TTF_CloseFont(middle_font);
    outter_font = nullptr;
    middle_font = nullptr;
    inner_font = nullptr;

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


int main()
{
    init();
    loadmedia();
    /*
    state = 1 -> start screen
    state = 2 -> ingame
    state = 3 -> endgame
    */
    int state = 1;
    // when adding level remember to change the max_level variable
    int level = 1, max_level = 4;

    /*
    quit is the game main loop
    when hold the mouse hold will turn true 
    if ball hit the hole pass_level turn true to load the waiting screen
    */
    bool quit = false, hold = false , pass_level = false;

    //just to get the init pos of the ball
    double init_pos_x = SCREEN_WIDTH/2 - ball.getW()/2;
    double init_pos_y = SCREEN_HEIGHT - tile*3 - ball.getH()/2; 

    //x and y is the continuously updated position of the ball
    double x = init_pos_x , y = init_pos_y;
     
    // my stupid logic to add friction
    double portion;

    // strokes count
    int strokes;
    // the position of the mouse to get velocity below when compared to position of the ball
    int shoot_x, shoot_y;
    double vel_x, vel_y , real_vel_x , real_vel_y;

    // the constant position of the hole
    const int hole_x = SCREEN_WIDTH/2 - hole.getW()/2 , hole_y =  tile*3 - hole.getH()/2; 

    SDL_Event e;
    while ( !quit )
    {
        while ( SDL_PollEvent( &e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if ( SDL_MOUSEBUTTONUP == e.type && SDL_BUTTON_LEFT == e.button.button && state == 1)
            {
                int mouse_x , mouse_y;
                SDL_GetMouseState(&mouse_x , &mouse_y);
                start(state , mouse_x, mouse_y , SCREEN_WIDTH/2 - start_game.getW()/2 , SCREEN_HEIGHT*2/3 - start_game.getH()/2 );
            }
            if ( SDL_MOUSEBUTTONDOWN == e.type && SDL_BUTTON_LEFT == e.button.button && real_vel_x == 0 && real_vel_y == 0 && state == 2 ) hold = true;
            
            if ( SDL_MOUSEBUTTONUP == e.type && SDL_BUTTON_LEFT == e.button.button && real_vel_x == 0 && real_vel_y == 0 && state == 2 )
            {

                if( pass_level )
                {
                    level++;
                    pass_level = false;
                } 
                else if (hold)
                {
                    strokes++;
                    SDL_GetMouseState ( &shoot_x , &shoot_y);
                    vel_x = -((double)shoot_x - (x+ball.getW()/2)) /4;
                    vel_y = -((double)shoot_y - (y+ball.getH()/2)) /4;
                    if (vel_x > 20) vel_x = 20;
                    else if (vel_x < -20) vel_x = -20;
                    if (vel_y > 20) vel_y = 20;
                    else if ( vel_y < -20) vel_y = -20;
                    portion = 0;
                    Mix_PlayChannel( -1 , swing , 0);
                }
                hold = false;
            }
            if ( SDL_MOUSEBUTTONUP == e.type && SDL_BUTTON_LEFT == e.button.button && state == 3)
            {
                int mouse_x , mouse_y;
                SDL_GetMouseState(&mouse_x , &mouse_y);
                restart(level ,strokes , state , mouse_x, mouse_y , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 + tile*2 );
                endgame(mouse_x , mouse_y ,SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + tile*4 + green_box.getH()/2 , quit );
            }
        }
        //start screen
        if ( state == 1 )
        {
            int mouse_x , mouse_y;
            SDL_GetMouseState(&mouse_x , &mouse_y);

            SDL_RenderClear(renderer);
            renderbackground(renderer);
            endscreen_overlay.render(renderer , 0 ,0);
            logo.render(renderer , SCREEN_WIDTH/2 - logo.getW()/2 , SCREEN_HEIGHT/3 - logo.getH()/2);
            light_up_white(renderer , white_box , mouse_x , mouse_y , SCREEN_WIDTH/2 , SCREEN_HEIGHT*2/3 );
            start_game.render(renderer , SCREEN_WIDTH/2 - start_game.getW()/2 , SCREEN_HEIGHT*2/3 - start_game.getH()/2);
        }
        // ingame
        else if ( state == 2 && !pass_level)
        {
            if (portion < 100 && ( abs(vel_x) >= 20 || abs(vel_y) >= 20 )) portion += 2;
            else if ( portion < 100 && ( abs(vel_x) < 20 || abs(vel_y) < 20)) portion += 4;
            else if ( portion < 100 && ( abs(vel_x) < 10 || abs(vel_y) < 10)) portion += 45;
            else if ( portion < 100 && ( abs(vel_x) < 5 || abs(vel_y) < 5)) portion += 50;
            else if ( portion < 100 && ( abs(vel_x) < 3 || abs(vel_y) < 3)) portion += 75;
            if ( portion > 100 ) portion = 100;
            real_vel_x = velocity_and_time( vel_x , portion);
            real_vel_y = velocity_and_time( vel_y , portion);
            check_wall_collision(x , y , vel_x , vel_y , real_vel_x , real_vel_y);
            if(check_hole( x , y )) { real_vel_x = 0; real_vel_y = 0; vel_x = 0 ; vel_y = 0; pass_level = true; Mix_PlayChannel(-1 , goal_sound , 0); }

            SDL_RenderClear(renderer);
            renderbackground(renderer);
            stroke_bg.render(renderer,0 , SCREEN_HEIGHT - stroke_bg.getH() );
            stroke_count.loadnumber(renderer,inner_font, strokes, "strokes: " , white );
            stroke_count.render (renderer,15 , SCREEN_HEIGHT - stroke_bg.getH() + 2);
            if ( hold )
            {
                double angle;
                SDL_GetMouseState( &shoot_x , &shoot_y);
                SDL_RendererFlip flip = SDL_FLIP_NONE;
                if ( x + ball.getW()/2 - shoot_x < 0) angle = atan( (y+ ball.getH()/2- shoot_y)/(x + ball.getW()/2 - shoot_x) )/M_PI*180 - 90; 
                else angle = atan( (y+ ball.getH()/2 - shoot_y)/(x + ball.getW()/2 - shoot_x) )/M_PI*180 + 90; 
                point.render_rotate(renderer,x + ball.getW()/2 - point.getW()/2 , y + ball.getH()/2 - point.getH()/2 , NULL , angle , NULL , flip );
            }
            ball.render(renderer, x , y );
            hole.render(renderer,hole_x , hole_y);
            // each case is for loading block tiles
            switch (level)
            {
            case 1:    
                break;
            case 2: {
                int block_x[15] = {tile*3, tile*4, tile*5, tile*6 , tile*0 ,tile* 1 , tile*2, tile*3 , tile*6 ,tile*7 ,tile*8 ,tile*9};
                int block_y[15] = {tile*8 , tile*8,tile*8 ,tile*8 , tile*4, tile*4, tile*4, tile*4, tile*4, tile*4, tile*4, tile*4};
                for (int i=0 ; i< 12 ; i++)
                {
                    block_tile.render1tile(renderer , block_x[i] , block_y[i]);
                    check_block_collision(x , y ,vel_x , vel_y , real_vel_x , real_vel_y , block_x[i] , block_y[i]);
                }
                break;
            }
            case 3: {
                int block_x[15] = {tile*4, tile*5, tile*5, tile*4 , tile*6, tile*6, tile*0 , tile*3 , tile*4, tile*8, tile*3, tile*8, tile*6};
                int block_y[15] = {tile*7, tile*8, tile*7, tile*8 , tile*2, tile*3, tile*3 , tile*5 , tile*4, tile*9, tile*10, tile*9, tile*11};

                for ( int i =0 ; i < 15 ; i++) 
                {
                    block_tile.render1tile(renderer , block_x[i] , block_y[i]);
                    check_block_collision(x, y , vel_x , vel_y , real_vel_x , real_vel_y , block_x[i] ,block_y[i]);
                }
                break;
            }
            case 4: {
                int block_x[15] = {tile*5 , tile*9 , tile*10, tile*8, tile*8, tile*5, tile*2, tile*3, tile*1, tile*7, tile*3, tile*6, tile*4, tile*6, tile*10};
                int block_y[15] = {tile*1, tile*7, tile*11, tile*12, tile*3, tile*7, tile*8, tile*9, tile*3, tile*11, tile*12, tile*8, tile*9, tile*3, tile*4};
                for ( int i =0 ; i < 15 ; i++) 
                {
                    block_tile.render1tile(renderer , block_x[i] , block_y[i]);
                    check_block_collision(x, y , vel_x , vel_y , real_vel_x , real_vel_y , block_x[i] ,block_y[i]);
                }
                break;
            }
            }
            if (level > max_level ) state++;
        }
        // waiting screen
        else if ( state == 2 && pass_level)
        {
            x = init_pos_x;
            y = init_pos_y;
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 107 , 142 , 35 , 0xff);
            wintext.render(renderer,SCREEN_WIDTH/2 - wintext.getW()/2 , SCREEN_HEIGHT/2 - wintext.getH());
            press_anywhere.render(renderer,SCREEN_WIDTH/2 - press_anywhere.getW()/2 , SCREEN_HEIGHT/2 ); 
        }
        // endgame
        else if ( state == 3 )
        {
            // set the position so there won't be any problem with the ball
            real_vel_x = 0;real_vel_y = 0;vel_x = 0; vel_y = 0; x = init_pos_x ; y = init_pos_y;
            int mouse_x , mouse_y;
            SDL_GetMouseState(&mouse_x , &mouse_y);

            SDL_RenderClear(renderer);
            render_endscreen(renderer);
            total_stroke.loadnumber(renderer , inner_font , strokes , "total strokes: " , white);
            pass_all_level.render(renderer, SCREEN_WIDTH/2 - pass_all_level.getW()/2 , SCREEN_HEIGHT/2 - pass_all_level.getH() - total_stroke.getH());
            total_stroke.render(renderer , SCREEN_WIDTH/2 - total_stroke.getW()/2 , SCREEN_HEIGHT/2 - total_stroke.getH() + 5);

            light_up_green(renderer, green_box , mouse_x , mouse_y , SCREEN_WIDTH/2 -green_box.getW()/2 , SCREEN_HEIGHT/2 + tile*2 - green_box.getH()/2 );
            play_again.render( renderer, SCREEN_WIDTH/2 - play_again.getW()/2 , SCREEN_HEIGHT/2 + tile*2 - play_again.getH()/2 );

            light_up_green(renderer, green_box, mouse_x , mouse_y , SCREEN_WIDTH/2 -green_box.getW()/2 , SCREEN_HEIGHT/2 + tile*4 );
            quit_game.render(renderer,  SCREEN_WIDTH/2 - quit_game.getW()/2 , SCREEN_HEIGHT/2 + tile*4 + green_box.getH()/2 - quit_game.getH()/2);
        }
        x += real_vel_x ; y += real_vel_y;
        
        SDL_RenderPresent(renderer);
        
    }

    close();

    return 0;
}
