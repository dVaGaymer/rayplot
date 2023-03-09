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
	axis_add_plot(&ax, plot_create_F(ax.x_range, cos, SOLID, NULL, ORANGE));
	ax.plots[0].title = "Cos";
	axis_add_plot(&ax, plot_create_F(ax.x_range, wave_test, SOLID, NULL, PINK));
	ax.plots[1].title = "wave_test";
	axis_add_plot(&ax, plot_create_F(ax.x_range, test, SCATTER, NULL, BLACK));
	ax.plots[2].title = "test";

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
		plot_update_one(&ax, 1);
		EndDrawing();
	}
	//TODO: check this function
	axis_destroy(&ax);
	CloseWindow();
}
