#include "main.h"
#include <stdio.h>

# define WIDTH 1200.0f
# define HEIGHT 800.0f

double test(double x) { return (sin(x) * cos(2 * x * x) * cos(2 * x)); }

double wave_test(double x) { return(sin (x - GetTime())); }

int	main(void)
{
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	t_axis2D	ax;
	axis_create(&ax, (Rectangle){WIDTH/2, HEIGHT/2, WIDTH * 0.9, 500});
	ax.x_range = (Vector3){-5, 0.01, 5};
	ax.y_range = (Vector3){-2, 0.01, 2};
	ax.title = "Hooke's Law";
	ax.x_label = "x / m";
	ax.y_label = "t / s";
	axis_add_plot(&ax, plot_create_F(ax.x_range, cos, SOLID, NULL, ORANGE));
	axis_add_plot(&ax, plot_create_F(ax.x_range, wave_test, SOLID, NULL, PINK));
	axis_add_plot(&ax, plot_create_F(ax.x_range, test, SCATTER, NULL, GREEN));

	t_hooke h;
	hooke_init(&h, 1000);
	hooke_reset(&h, 2, 0.01, 5, 0.4, 0);
	hooke_vel_data(&h);
	axis_add_plot(&ax, plot_create_D(h.steps, h.data + 1, SOLID, NULL, BLACK));

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		DrawFPS(0, 0);
		axis_show(ax);
		plot_update_one(ax, 1);
		EndDrawing();
	}
	axis_destroy(ax);
	CloseWindow();
}
