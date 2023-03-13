#include "main.h"
#include <stdio.h>

double cosT(double x) { return(sin (x - GetTime())); }

void	UpdateDrawFrame(void)
{
		//Update data each time
		br_func(pl.x_data, pl.size, cosT, pl.y_data);
		BeginDrawing();
		ClearBackground(WHITE);
		DrawFPS(0, 0);

		axis_show(&ax);
		EndDrawing();
}

int	main(void)
{
	atexit(l);
	InitWindow(WIDTH + PANEL_WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	//Animation
	// Vector2	point = (Vector2){.x=0, .y=0};
	// Vector2	rect = (Vector2){.x=PANEL_WIDTH + WIDTH/2, .y=HEIGHT/2};
	// float	t = 0;
	float	tf = 0.8 * 5;

	t_axis2D	ax;
	axis_create(&ax, (Rectangle){PANEL_WIDTH + WIDTH/4, HEIGHT/4, WIDTH * 0.5, 400});
	ax.x_range = (Vector3){0, 0.01, tf};
	ax.y_range = (Vector3){-2, 0.01, 2};
	ax.title = "Hooke's Law";
	ax.x_label = "t / s";
	ax.y_label = "x / m";

	t_axis2D	ax1;
	axis_create(&ax1, (Rectangle){PANEL_WIDTH + WIDTH - WIDTH/4, HEIGHT/4, WIDTH * 0.5, 400});
	ax1.x_range = (Vector3){0, 0.01, tf};
	ax1.y_range = (Vector3){-2, 0.01, 2};
	ax1.title = "Total Energy";
	ax1.x_label = "t / s";
	ax1.y_label = "E / J";

	t_axis2D	ax2;
	axis_create(&ax2, (Rectangle){PANEL_WIDTH + WIDTH/4, HEIGHT - HEIGHT/4, WIDTH * 0.5, 400});
	ax2.x_range = (Vector3){0, 0.01, tf};
	ax2.y_range = (Vector3){-10, 0.01, 10};
	ax2.title = "Velocity";
	ax2.x_label = "t / s";
	ax2.y_label = "V / m/s";

	// t_axis2D	ax2;
	// axis_create(&ax2, (Rectangle){.x=PANEL_WIDTH + WIDTH/2, .y=HEIGHT*6/8, 700, 300});
	// ax2.x_range = (Vector3){.x=-0.8, .y = 0.01, .z=0.8};
	// ax2.y_range = (Vector3){.x=-0.3, .y = 0.01, .z=0.3};
	// ax2.legend = false;

	t_hooke h;
	hooke_init(&h, 1000);
	// k = 2 | m = 0.01 | v0 = 0
	// hooke_reset(&h, 2, 0.01, 6, 0.4, 0); //T = 2pi/sqrt(k/m) = 0.444
	// k = 10 | m = 0.1 | v0 = 0
	// hooke_reset(&h, 10, 0.1, tf, 0.6, 0); //T = 2pi/sqrt(k/m) = 0.628
	// k = 5 | m = 0.5 | v0 = 0
	hooke_reset(&h, 5, 0.5, tf, 0.6, 0); //T = 2pi/sqrt(k/m) = 1.98
	hooke_vel_data(&h);
	hooke_Ep_data(&h);
	hooke_Ec_data(&h);
	hooke_E_data(&h);
	// char *title = strdup(TextFormat("Hooke T=%.2f", 0.0));
	axis_add_plot(&ax, plot_DV(h.steps, h.data));
	ax.plots[0].type = SOLID;
	ax.plots[0].title = "Hooke";
	ax.plots[0].color = RED;

	axis_add_plot(&ax1, plot_DV(h.steps, h.E_data));
	ax1.plots[0].title = "E";
	ax1.plots[0].type = SOLID;
	ax1.plots[0].color = BLACK;
	axis_add_plot(&ax1, plot_DV(h.steps, h.Ec_data));
	ax1.plots[1].title = "Ec";
	ax1.plots[1].type = SOLID;
	ax1.plots[1].color = BLUE;
	axis_add_plot(&ax1, plot_DV(h.steps, h.Ep_data));
	ax1.plots[2].title = "Ep";
	ax1.plots[2].type = SOLID;
	ax1.plots[2].color = PURPLE;

	axis_add_plot(&ax2, plot_DV(h.steps, h.vel_data));
	ax2.plots[0].title = "vel";
	ax2.plots[0].type = SOLID;
	ax2.plots[0].color = ORANGE;

	//RAYGUI
	GuiLoadStyle("./styles/jungle/jungle.rgs");
	float	k_value = 2, m_value = 0.01;
	float	k_value_prev = 2, m_value_prev = 0.01;
	while (!WindowShouldClose())
	{
		/* AXIS */
		//--------------------------------------------------------------------------------------
		// free(ax.plots[0].title);
		// title = strdup(TextFormat("%.1f %.1f %.1f", h.k, h.m, hooke_get_period(h)));
		// ax.plots[0].title = title;

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
		DrawFPS(PANEL_WIDTH + WIDTH - 75, 0);
		axis_show(&ax);
		axis_show(&ax1);
		axis_show(&ax2);
		//--------------------------------------------------------------------------------------

		/* RAYGUI */
		//--------------------------------------------------------------------------------------
		GuiPanel((Rectangle){0, 0, PANEL_WIDTH, HEIGHT}, "  Hook's Attributes");
		DrawText("K", PANEL_WIDTH/2, 110, 20, WHITE);
		k_value = GuiSlider((Rectangle){PANEL_WIDTH/2 - 50, 130, 100, 30}, "1", "10", k_value, 1, 10);
		if (k_value != k_value_prev)
		{
			k_value_prev = k_value;
			hooke_set_k(&h, k_value);
			hooke_vel_data(&h);
			hooke_E_data(&h);
			hooke_Ep_data(&h);
			hooke_Ec_data(&h);
		}
		DrawText("m", PANEL_WIDTH/2, 170, 20, WHITE);
		m_value = GuiSlider((Rectangle){PANEL_WIDTH/2 - 50, 190, 100, 30}, "0.01", "0.5", m_value, 0.01, 0.5);
		if (m_value != m_value_prev)
		{
			m_value_prev = m_value;
			hooke_set_m(&h, m_value);

		}
		if (GuiButton((Rectangle){PANEL_WIDTH/2 - 25, 50, 50, 50}, "Reset"))
		{
			k_value = 2;
			m_value = 0.01;
			hooke_set_m(&h, m_value);
			hooke_set_k(&h, k_value);
		}
		hooke_vel_data(&h);
		hooke_E_data(&h);
		hooke_Ep_data(&h);
		hooke_Ec_data(&h);
		//--------------------------------------------------------------------------------------

		/* RECTANGLE ANIMATION */
		//--------------------------------------------------------------------------------------  RECTANGLE ANIMATION
		//TODO: IMPROVE AND AUTOMATE ANIMATIONS
		// t+=GetFrameTime();
		// if (t>=tf) t = GetFrameTime();
		// DrawCircle(point.x, point.y, 5, RED);
		// point = axis_map_to_screen(&ax, (Vector2){h.data[(int)(t/h.d_t)].x, h.data[(int)(t/h.d_t)].y});
		// axis_show(&ax2);
		// rect = axis_map_to_screen(&ax2, (Vector2){h.data[(int)(t/h.d_t)].y, 0});
		// // l1 = axis_map_to_screen(ax2, 0, 1);
		// // l2 = axis_map_to_screen(ax2, 0, -1);
		// // DrawLine(l1.x, l1.y, l2.x, l2.y, WHITE);
		// DrawRectangle(rect.x-25, rect.y-25, 50, 50, LIGHTGRAY);
		//------------------------------------------------------------------------------------------
		EndDrawing();
	}
	free(ax.plots[0].title);
	hooke_destroy(&h);
	//axis_destroy(&ax);
	CloseWindow();
}
