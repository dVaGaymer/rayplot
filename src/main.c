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
	ax.title = "TEST";
	ax.x_label = "TEST X";
	ax.y_label = "TEST Y";
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
		BeginDrawing();
		ClearBackground(WHITE);
		DrawFPS(0, 0);
		axis_show(&ax);
		plot_update_one(&ax, 1);
		EndDrawing();
	}
	axis_destroy(&ax);
	CloseWindow();
}
