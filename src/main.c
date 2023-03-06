#include "main.h"

# define WIDTH 800.0f
# define HEIGHT 800.0f

int	main(void)
{
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(0, 0);
		EndDrawing();
	}
}
