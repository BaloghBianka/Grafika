all:
	gcc -Iinclude/ src/ball.c src/game.c src/main.c src/pad.c src/pong.c -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm -o pong.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/ball.c src/game.c src/main.c src/pad.c src/pong.c -lSDL2 -lGL -lm -o pong -Wall -Wextra -Wpedantic
mac:
	gcc -Iinclude/ src/ball.c src/game.c src/main.c src/pad.c src/pong.c \
	    $(shell sdl2-config --cflags --libs) -framework OpenGL -lm \
	    -o pong -Wall -Wextra -Wpedantic
