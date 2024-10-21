#/bin/bash

gcc -Wall -Werror -Wextra main.c -o game $(sdl2-config --cflags --libs) -lSDL2_image
