## Overall:
GOLF 2D is a game which purpose is trying to bring the golf ball to the hole. There are currently 4 level with special obsticals.
![image 1](stuff/for%20readme/screen_shot_1.png)

Before you continue and run the game, make sure to have SDL2 libraries installed. 
In detail: SDL2, SDL_ttf, SDL_mixer and SDL_image.

## Initial the game:
Type make in terminal to make .o file, even if they're already there. And press enter on windows or return on macs.
Type ./golf and then enter (window) or return (mac).


## instruction: 
use the mouse as a nevigator. 
Hold the mouse to see the direction where the ball will go. 
![image 2](stuff/for%20readme/screen_shot_2.png)
Release the mouse to shoot the ball.
 *note: the further the cursor is from the golf ball, the stronger is your stroke.

Try your best to have as few strokes as possible!!

## game update:
to add level, you need to create a new even number level in golf.cpp, then create an array, add block in it and check for collision like i did.

if there are problems about collision, to fix it open the ball_util.cpp and check for errors.

all of the png pictures i used is in the "stuff" folder, if you want to add more function, please put png pictures in the folder.
