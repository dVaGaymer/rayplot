#include "main.h"
#include <stdio.h>

double test(double x) { return (sin(x) * cos(2 * x * x) * cos(2 * x)); }

double wave_test(double x) { return(sin (x - GetTime())); }

int	main(void)
{
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	t_axis2D	ax;
	axis_create(&ax, (Rectangle){WIDTH/2, HEIGHT/2, WIDTH * 0.9, 500});
	ax.title = "Some cool Plots";
	ax.x_label = "X axis";
	ax.y_label = "Y axis";
	ax.x_range = (Vector3){-10, 0.01 , 10};
	ax.y_range = (Vector3){-1.5, 0.01, 1.5};
	axis_add_plot(&ax, plot_D(3, (float [3]){0, 1, 2}, (float [3]){0, 1, 2}));
	ax.plots[0].title = "Cos";
	ax.plots[0].type = SOLID;
	ax.plots[0].color = GREEN;
	axis_add_plot(&ax,
		plot_DV(4,
			(Vector2 [])
				{
					(Vector2){0, 0},
					(Vector2){0, 1},
					(Vector2){-5, 1},
					(Vector2){-5, -1}
				}));
	ax.plots[0].title = "Cos";
	ax.plots[0].type = SOLID;
	ax.plots[0].color = GREEN;

	while (!WindowShouldClose())
	{
		/* INPUT TESTS */
		if (IsKeyDown('W'))
			ax.bounds.y -= 3;
		if (IsKeyDown('A'))
			ax.bounds.x -= 3;
		if (IsKeyDown('S'))
			ax.bounds.y += 3;
		if (IsKeyDown('D'))
			ax.bounds.x += 3;

		BeginDrawing();
		ClearBackground(WHITE);
		DrawFPS(0, 0);
		axis_show(&ax);
		EndDrawing();
	}
	axis_destroy(&ax, (void *)plot_destroy);
	CloseWindow();
}
