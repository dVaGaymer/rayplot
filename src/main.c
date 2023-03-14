#include "main.h"
#include <stdio.h>

/*-------------------------------------------------------*/
/*       Local variables (LOCAL TO THIS MODULE)          */
/*       (module variables ~~> class variables)          */
/*-------------------------------------------------------*/
t_axis2D	ax;
t_plot		pl;

double cosT(double x) { return(sin (x - GetTime())); }

void	UpdateDrawFrame(void)
{
		//Update data each time
		brFunctionOverArray(pl.x_data, pl.size, cosT, pl.y_data);
		BeginDrawing();
		ClearBackground(WHITE);
		DrawFPS(0, 0);

		axShow(&ax);
		EndDrawing();
}

int	main(void)
{
	InitWindow(WIDTH, HEIGHT, "Rayplot Example");
	SetTargetFPS(60);

	//Create Axis
	axCreate(&ax, (Rectangle){WIDTH/2, HEIGHT/2, WIDTH * 0.8, HEIGHT * 0.8});
	ax.x_range = (Vector3){0, 0.01, 10};
	ax.y_range = (Vector3){-1.5, 0, 1.5};
	ax.title = "Moving cosine";
	ax.x_label = "X label";
	ax.y_label = "Y label";

	//Create plot
	float		*x_range = ranCreate(ax.x_range);
	float		*y_range = ranCreate(ax.x_range);
	size_t		size = ranGetSize(ax.x_range);
	pl = plCreate(size, x_range, brFunctionOverArray(x_range, size, cosT, y_range));
	pl.title = "Cos(x - t)";
	pl.color = GREEN;
	pl.marker_size = 3;

	//Add plot to axis
	axAddPlot(&ax, pl);
	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}
	free(x_range);
	free(y_range);
	CloseWindow();
}
