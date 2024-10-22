#/bin/bash

gcc -Wall -Werror -Wextra main.c class.c -o game $(sdl2-config --cflags --libs) -lSDL2_image
