#include "rayplot.h"

//TODO: Send to plot lines, the t_plot directly
static void	_plot_lines_D(t_axis2D const *ax, t_plot const *pl)
{
	Vector2	prev;
	Vector2	p;
	prev = axis_map_to_screen(ax, (Vector2)pl->data[0]);

	for (int i = 0; i < pl->size - 1; i++)
	{
		p = axis_map_to_screen(ax, (Vector2)pl->data[i]);
		DrawLineEx(prev, p, pl->marker_size, pl->color);
		prev = p;
	}
}

static void	_plot_scatter_D(t_axis2D const *ax, t_plot *pl)
{
	for (int i = 0; i < pl->size; i++)
		DrawCircleV(axis_map_to_screen(ax, (Vector2)pl->data[i]), pl->marker_size, pl->color);
}

void	plot(t_axis2D const *ax, t_plot pl)
{
	if (!pl.enabled)
		return ;
	if (SOLID == pl.type)
		_plot_lines_D(ax, &pl);
	else if (SCATTER == pl.type)
		_plot_scatter_D(ax, &pl);
}

//Not a good signatura, this should belong to axis?
void	plot_update_one(t_axis2D *ax, int id)
{
	t_plot	pl = ax->plots[id];

	for (int i = 0; i < pl.size; i ++)
		pl.data[i] = (Vector2){pl.range.x + pl.range.y * i, pl.func(pl.range.x + pl.range.y * i)};
}

t_plot	plot_create_F(Vector3 range, t_func1 f, t_line_type type, char *title, Color col)
{
	t_plot	pl;
	pl.range = range;
	pl.func = f;

	pl.size = (range.z - range.x) / range.y;
	pl.data = (Vector2 *)malloc(sizeof(Vector2) * pl.size);
	for (int i = 0; i < pl.size; i ++)
		pl.data[i] = (Vector2){pl.range.x + pl.range.y * i, pl.func(pl.range.x + pl.range.y * i)};

	pl.type = type;
	pl.title = title;
	pl.color = col;
	pl.enabled = true;
	pl.marker_size = DEFAULT_MARKER_SIZE;
	return (pl);
}

t_plot	plot_create_D(int size, Vector2 *data, t_line_type type, char *title, Color col)
{
	t_plot	pl;

	pl.data = data;
	pl.func = NULL;
	pl.size = size;
	pl.range = NULL_VECTOR3;
	pl.type = type;
	pl.title = title;
	pl.color = col;
	pl.marker_size = DEFAULT_MARKER_SIZE;
	pl.enabled = true;
	return (pl);
}

void	plot_destroy(t_plot pl)
{
	if (pl.data)
		free(pl.data);
}

/* FOLLOWING FUNCTIONS WILL WORK OVER NEWLY CREATED PLOT*/
/*
t_axis2D	plot_lines_F(Vector3 range, double (*f)(double), Color col)
{
	t_axis2D	ax; //create standar axis, draw to it, and return it (same as julia makie)

	Vector2	prev;
	Vector2	p;
	prev = axis_map_to_screen(ax, (Vector2){range.x, f(range.x)});
	for (float i = range.x; i < range.z; i += range.y)
	{
		p = axis_map_to_screen(ax, (Vector2){i, f(i)});
		DrawLineV(prev, p, col);
		prev = p;
	}
	return ax;
}

t_axis2D	plot_scatter_F(Vector3 range, double (*f)(double), Color col)
{
	t_axis2D	ax; //create standar axis, draw to it, and return it (same as julia makie)

	for (float i = range.x; i < range.z; i += range.y)
		DrawPixelV(axis_map_to_screen(ax, (Vector2){i, f(i)}), col);
	return ax;
}
*/
