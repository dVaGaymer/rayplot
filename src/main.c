#include "main.h"
#include <stdio.h>

/*-------------------------------------------------------*/
/*       Local variables (LOCAL TO THIS MODULE)          */
/*       (module variables ~~> class variables)          */
/*-------------------------------------------------------*/
static t_axis2D		ax;
static t_plot		pl;

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
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	//Create Axis
	axis_create(&ax, (Rectangle){WIDTH/2, HEIGHT/2, WIDTH * 0.8, HEIGHT * 0.8});
	ax.x_range = (Vector3){0, 0.01, 10};
	ax.y_range = (Vector3){-1.5, 0, 1.5};
	ax.title = "Moving cosine";
	ax.x_label = "X label";
	ax.y_label = "Y label";

	//Create plot
	float		*x_range = range_create(ax.x_range);
	float		*y_range = range_create(ax.x_range);
	size_t		size = range_size(ax.x_range);
	pl = plot_D(size, x_range, br_func(x_range, size, cosT, y_range));
	pl.title = "Cos(x - t)";
	pl.color = GREEN;
	pl.marker_size = 3;

	//Add plot to axis
	axis_add_plot(&ax, pl);
	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}
	free(x_range);
	free(y_range);
	CloseWindow();
}
