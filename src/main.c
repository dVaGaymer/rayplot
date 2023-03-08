#include "main.h"

# define WIDTH 1000.0f
# define HEIGHT 1000.0f

double test(double x) { return (sin(x) * cos(2 * x * x) * cos(2 * x)); }

int	main(void)
{
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	t_axis2D	ax;
	axis_create(&ax, (Rectangle){WIDTH/2, HEIGHT/2, 900, 300});
	ax.x_range = (Vector2){-5, 5 * PI};
	ax.y_range = (Vector2){-1.5, 1.5};
	ax.title = "TEST";
	ax.x_label = "TEST X";
	ax.y_label = "TEST Y";

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(0, 0);

		plot_lines_F(ax, cos, (Vector3){-10, 0.1, 10 * PI}, ORANGE);
		plot_lines_F(ax, sin, (Vector3){-10, 0.1, 10 * PI}, RED);
		plot_lines_F(ax, exp, (Vector3){-10, 0.1, 3}, GREEN);
		plot_lines_F(ax, test, (Vector3){-10, 0.05, 10 * PI}, PINK);
		axis_show(ax);

		EndDrawing();
	}
}
