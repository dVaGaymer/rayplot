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
	ax.x_range = (Vector3){2.8, 0.01 , 4};
	ax.y_range = (Vector3){0, 0.01, 1};

	Vector3	range = ax.x_range;
	float	*x = range_create(range), *y = range_create(range);
	axis_add_plot(&ax, plot_D(range_size(range), x, br_func(x, range_size(range), cos2, y)));
	ax.plots[0].title = "wave";
	ax.plots[0].type = SOLID;
	ax.plots[0].color = PINK;

	Vector3	range1 = ax.x_range;
	float	*x1 = range_create(range1), *y1 = range_create(range1);
	axis_add_plot(&ax, plot_D(range_size(range1), x1, br_func(x1, range_size(range1), cosT, y1)));
	ax.plots[1].title = "cosT";
	ax.plots[1].type = SOLID;
	ax.plots[1].color = GREEN;

	Vector2 *f = csv_readV2("./src/csv/feig.csv");
	// csv_writeV2("./src/csv/out.csv", f, csv_get_size("./src/csv/test.csv"));

	axis_add_plot(&ax, plot_DV(csv_get_size("./src/csv/feig.csv"), f));
	ax.plots[2].title = "points";
	ax.plots[2].type = SCATTER;
	ax.plots[2].color = BLUE;
	ax.plots[2].marker_size = 1;
	while (!WindowShouldClose())
	{
		br_func(x,range_size(range), cos2, y);
		br_func(x1, range_size(range1), cosT, y1);
		/* INPUT TESTS */
		if (IsKeyDown('W'))
			ax.bounds.y -= 3;
		if (IsKeyDown('A'))
			ax.bounds.x -= 3;
		if (IsKeyDown('S'))
			ax.bounds.y += 3;
		if (IsKeyDown('D'))
			ax.bounds.x += 3;
		if (IsKeyDown('-'))
		{
			ax.x_range.x -= 0.1;
			ax.x_range.z += 0.1;

			ax.y_range.x -= 0.1;
			ax.y_range.z += 0.1;
		}
		if (IsKeyDown('='))
		{
			ax.x_range.x += 0.1;
			ax.x_range.z -= 0.1;

			ax.y_range.x += 0.1;
			ax.y_range.z -= 0.1;
		}

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
