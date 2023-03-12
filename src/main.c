#include "main.h"
#include <stdio.h>

double cos2(double x) { return (sin(x) * cos(2 * x * x) * cos(2 * x)); }

double cosT(double x) { return(sin (x - GetTime())); }

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

	float	*x = range_create(ax.x_range), *y = range_create(ax.x_range);
	axis_add_plot(&ax, plot_D(range_size(ax.x_range), x, br_func(x, range_size(ax.x_range), cos2, y)));
	ax.plots[0].title = "wave";
	ax.plots[0].type = SOLID;
	ax.plots[0].color = PINK;

	float	*x1 = range_create(ax.x_range), *y1 = range_create(ax.x_range);
	axis_add_plot(&ax, plot_D(range_size(ax.x_range), x1, br_func(x1, range_size(ax.x_range), cosT, y1)));
	ax.plots[1].title = "cosT";
	ax.plots[1].type = SOLID;
	ax.plots[1].color = GREEN;


	while (!WindowShouldClose())
	{
		br_func(x,range_size(ax.x_range), cos2, y);
		br_func(x1, range_size(ax.x_range), cosT, y1);
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
	free(x); free(y); free(x1); free(y1);
	CloseWindow();
}
