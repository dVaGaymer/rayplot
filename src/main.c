#include "main.h"
#include <stdio.h>

double test(double x) { return (sin(x) * cos(2 * x * x) * cos(2 * x)); }

double wave_test(double x) { return(sin (x - GetTime())); }

void l(){system("leaks rayplot");}

int	main(void)
{
	atexit(l);
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	t_axis2D	ax;
	axis_create(&ax, (Rectangle){WIDTH/2, HEIGHT/2, WIDTH * 0.9, 500});
	ax.x_range = (Vector3){0, 0.01, 6};
	ax.y_range = (Vector3){-6, 0.01, 6};
	ax.title = "Hooke's Law";
	ax.x_label = "x / m";
	ax.y_label = "t / s";
	// axis_add_plot(&ax, plot_create_F(ax.x_range, cos, SOLID, NULL, ORANGE));
	// ax.plots[0].title = "cos(x)";
	// axis_add_plot(&ax, plot_create_F(ax.x_range, wave_test, SOLID, NULL, PINK));
	// ax.plots[1].title = "wave_test";
	// axis_add_plot(&ax, plot_create_F(ax.x_range, test, SCATTER, NULL, GREEN));
	// ax.plots[2].title = "test";

	t_hooke h;
	hooke_init(&h, 1000);
	// k = 2 | m = 0.01 | v0 = 0
	// hooke_reset(&h, 2, 0.01, 6, 0.4, 0); //T = 2pi/sqrt(k/m) = 0.444
	// k = 10 | m = 0.1 | v0 = 0
	hooke_reset(&h, 10, 0.1, 6, 0.4, 0); //T = 2pi/sqrt(k/m) = 0.628
	// k = 5 | m = 0.5 | v0 = 0
	hooke_reset(&h, 5, 0.5, 6, 0.4, 0); //T = 2pi/sqrt(k/m) = 1.98
	hooke_vel_data(&h);
	char *title = strdup(TextFormat("Hooke T=%.2f", 0.0));
	axis_add_plot(&ax, plot_create_D(h.steps, h.data, SOLID, NULL, RED));
	ax.plots[0].title = title;
	axis_add_plot(&ax, plot_create_D(h.steps, h.vel_data, SOLID, NULL, ORANGE));
	ax.plots[1].title = "vel";
	//Need to strdup the return of TextFormat
	while (!WindowShouldClose())
	{
		free(ax.plots[0].title);
		title = strdup(TextFormat("Hooke T=%.2fs", hooke_get_period(h)));
		ax.plots[0].title = title;
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
		DrawFPS(WIDTH - 75, 0);
		axis_show(&ax);
		EndDrawing();

		/* RAYGUI */
		// GuiPanel((Rectangle){0, 0, 50, HEIGHT}, "");
		// GuiSlider((Rectangle){50/2 - 25, 130, 50, 30}, "", "", 0, 1, 10);
	}
	free(ax.plots[0].title);
	axis_destroy(&ax);
	CloseWindow();
}
