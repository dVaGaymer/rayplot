#include "main.h"

# define WIDTH 1000.0f
# define HEIGHT 1000.0f

double test(double x) { return (sin(x) * cos(2 * x * x) * cos(2 * x)); }

int	main(void)
{
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	t_axis2D	ax;
	axis_create(&ax, (Rectangle){WIDTH/2, HEIGHT/2, 900, 500});
	ax.x_range = (Vector2){0, 1.5};
	ax.y_range = (Vector2){-6, 6};
	ax.title = "Hooke's Law";
	ax.x_label = "x / m";
	ax.y_label = "t / s";
	t_hooke h;
	hooke_init(&h, 1000);
	hooke_reset(&h, 2, 0.01, 1.5, 0.4, 0);
	hooke_vel_data(&h);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(0, 0);

		// plot_lines_F(ax, cos, (Vector3){-10, 0.1, 10 * PI}, ORANGE);
		// plot_lines_F(ax, sin, (Vector3){-10, 0.1, 10 * PI}, RED);
		// plot_lines_F(ax, exp, (Vector3){-10, 0.1, 3}, GREEN);
		// plot_lines_F(ax, test, (Vector3){-10, 0.05, 10 * PI}, PINK);
		plot_lines_D(ax, h.data + 1, h.steps, PINK);
		plot_lines_D(ax, h.vel_data + 1, h.steps, ORANGE);
		axis_show(ax);

		EndDrawing();
	}
}
