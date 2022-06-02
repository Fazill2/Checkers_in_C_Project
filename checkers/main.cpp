#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

constexpr auto SCREEN_WIDTH =  1200;;
constexpr auto SCREEN_HEIGHT = 800;;


int main ()
{
	// set up the window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

	
	// game loop
	while (!WindowShouldClose())
	{
		// drawing
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("hello", 200,200,20,WHITE);
		
		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;
}