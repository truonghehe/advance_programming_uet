CC=g++

CFLAGS=-c -Wall

INCLUDE=-I/Library/Frameworks/SDL2.framework -I/Library/Frameworks/SDL2_image.framework -I/Library/Frameworks/SDL2_ttf.framework -I/Library/Frameworks/SDL2_mixer.framework

LIB=-F/Library/Frameworks -framework SDL2 -F/Library/Frameworks -framework SDL2_image -F/Library/Frameworks -framework SDL2_ttf -F/Library/Frameworks -framework SDL2_mixer

golf: golf.o background.o ball_util.o end.o my_class.o
	$(CC) golf.o background.o ball_util.o end.o my_class.o $(INCLUDE) $(LIB) -o golf

golf.o: golf.cpp
	$(CC) $(CFLAGS) golf.cpp $(INCLUDE) $(LIB) -o golf.o

background.o: background.cpp
	$(CC) $(CFLAGS) background.cpp

ball_util.o: ball_util.cpp
	$(CC) $(CFLAGS) ball_util.cpp

end.o: end.cpp
	$(CC) $(CFLAGS) end.cpp

my_class.o: my_class.cpp
	$(CC) $(CFLAGS) my_class.cpp

clean:
	rm *.o golf