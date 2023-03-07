#include "main.h"

# define WIDTH 1000.0f
# define HEIGHT 1000.0f

int	main(void)
{
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	t_axis2D	ax;
	axis_create(&ax, (Rectangle){WIDTH/2, HEIGHT/2, 500, 500});
	ax.x_range = (Vector2){0, 10};
	ax.y_range = (Vector2){-1, 1};
	ax.title = "TEST";
	ax.x_label = "TEST X";
	ax.y_label = "TEST Y";

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(0, 0);

		plot_lines_F(ax, cos, (Vector3){0, 0.1, 10}, ORANGE);
		axis_show(ax);
		// DrawCircleV((Vector2){400, 400}, 200, WHITE);
		DrawText(TextFormat("%.2f", 1.213123f), 100, 100, 30, WHITE);

		EndDrawing();
	}
}
