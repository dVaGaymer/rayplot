#include "rayplot.h"

//TODO: Send to plot lines, the t_plot directly
static void	_draw_solid_D(t_axis2D const *ax, t_plot const *pl)
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

static void	_draw_scatter_D(t_axis2D const *ax, t_plot *pl)
{
	for (int i = 0; i < pl->size; i++)
		DrawCircleV(axis_map_to_screen(ax, (Vector2)pl->data[i]), pl->marker_size, pl->color);
}

void	plot_draw(t_axis2D const *ax, t_plot pl)
{
	if (!pl.enabled)
		return ;
	if (SOLID == pl.type)
		_draw_solid_D(ax, &pl);
	else if (SCATTER == pl.type)
		_draw_scatter_D(ax, &pl);
}

//funcion de mie®∂å
//Not a good signatura, this should belong to axis?
void	plot_recal(t_axis2D *ax, int id)
{
	t_plot	pl = ax->plots[id];

	for (int i = 0; i < pl.size; i ++)
		pl.data[i] = (Vector2){pl.range.x + pl.range.y * i, pl.func(pl.range.x + pl.range.y * i)};
}

t_plot	plot_F(Vector3 range, t_func1 f)
{
	t_plot	pl;
	pl.range = range;
	pl.func = f;

	pl.size = (range.z - range.x) / range.y;
	pl.data = (Vector2 *)malloc(sizeof(Vector2) * pl.size);
	for (int i = 0; i < pl.size; i ++)
		pl.data[i] = (Vector2){pl.range.x + pl.range.y * i, pl.func(pl.range.x + pl.range.y * i)};

	pl.type = DEFAULT_TYPE;
	pl.title = DEFAULT_TITLE;
	pl.color = DEFAULT_COLOR;
	pl.enabled = true;
	pl.marker_size = DEFAULT_MARKER_SIZE;
	return (pl);
}

t_plot	plot_D(int size, Vector2 *data)
{
	t_plot	pl;

	pl.data = data;
	pl.func = NULL;
	pl.size = size;
	pl.range = NULL_VECTOR3;
	pl.type = DEFAULT_TYPE;
	pl.title = DEFAULT_TITLE;
	pl.color = DEFAULT_COLOR;
	pl.marker_size = DEFAULT_MARKER_SIZE;
	pl.enabled = true;
	return (pl);
}

t_plot	plot_MAP(int size, Vector2 *data, t_func1 f, bool inverse)
{
	t_plot	pl;

	pl.size = size;
	pl.data = (Vector2 *)malloc(sizeof(Vector2) * pl.size);
	if (!f)
		return (t_plot){};
	if (!inverse)
		for (int i = 0; i < size; i++)
		{
			pl.data[i].y = f(data[i].x);
			pl.data[i].x = data[i].x;
		}
	else
		for (int i = 0; i < size; i++)
		{
			pl.data[i].y = f(data[i].y);
			pl.data[i].x = data[i].x;
		}
	pl.func = f;
	pl.range = NULL_VECTOR3;
	pl.type = DEFAULT_TYPE;
	pl.title = DEFAULT_TITLE;
	pl.color = DEFAULT_COLOR;
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
