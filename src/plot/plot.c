#include "rayplot.h"

void	plot_lines_D(t_axis2D ax, Vector2 *data, int size, Color col)
{
	Vector2	prev;
	Vector2	p;
	prev = axis_map_to_screen(ax, (Vector2)data[0]);
	for (int i = 0; i < size - 1; i++)
	{
		p = axis_map_to_screen(ax, (Vector2)data[i]);
		DrawLineV(prev, p, col);
		prev = p;
	}
}

void	plot_scatter_D(t_axis2D ax, Vector2 *data, int size, Color col)
{
	for (int i = 0; i < size; i++)
		DrawPixelV(axis_map_to_screen(ax, data[i]), col);
	axis_show(ax);
}

//EACH CALL DO ALL THE CALCULATIONS AGAIN
void	plot_lines_F(t_axis2D ax, double (*f)(double), Vector3 range, Color col)
{
	Vector2	prev;
	Vector2	p;
	prev = axis_map_to_screen(ax, (Vector2){range.x, f(range.x)});
	for (float i = range.x; i < range.z; i += range.y)
	{
		p = axis_map_to_screen(ax, (Vector2){i, f(i)});
		DrawLineV(prev, p, col);
		prev = p;
	}
}

//EACH CALL DO ALL THE CALCULATIONS AGAIN
void	plot_scatter_F(t_axis2D ax, double (*f)(double), Vector3 range, Color col)
{
	for (float i = range.x; i < range.z; i += range.y)
		DrawPixelV(axis_map_to_screen(ax, (Vector2){i, f(i)}), col);
}
