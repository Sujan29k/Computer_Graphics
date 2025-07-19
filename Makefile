main: main.c
	gcc main.c -o main -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit
