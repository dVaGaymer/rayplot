#include "rayplot.h"
#include <stdio.h>
static void	_draw_solid_D(t_axis2D const *ax, t_plot const *pl)
{
	Vector2	prev;
	Vector2	p;
	if (pl->points_data)
	{
		prev = axis_map_to_screen(ax, (Vector2)pl->points_data[0]);

		for (int i = 0; i < pl->size; i++)
		{
			p = axis_map_to_screen(ax, (Vector2)pl->points_data[i]);
			DrawLineEx(prev, p, pl->marker_size, pl->color);
			prev = p;
		}
	}
	else
	{
		prev = axis_map_to_screen(ax, (Vector2){pl->x_data[0], pl->y_data[0]});

		for (int i = 0; i < pl->size; i++)
		{
			p = axis_map_to_screen(ax, (Vector2){pl->x_data[i], pl->y_data[i]});
			DrawLineEx(prev, p, pl->marker_size, pl->color);
			prev = p;
		}
	}
}

static void	_draw_scatter_D(t_axis2D const *ax, t_plot const *pl)
{
	if (pl->points_data)
		for (int i = 0; i < pl->size; i++)
			DrawCircleV(axis_map_to_screen(ax, (Vector2)pl->points_data[i]), pl->marker_size, pl->color);
	else
		for (int i = 0; i < pl->size; i++)
			DrawCircleV(axis_map_to_screen(ax, (Vector2){pl->x_data[i], pl->y_data[i]}), pl->marker_size, pl->color);
}

void	plot_draw(t_axis2D const *ax, int id)
{
	t_plot const	*pl = &ax->plots[id];

	if (!pl->enabled)
		return ;
	if (SOLID == pl->type)
		_draw_solid_D(ax, pl);
	else if (SCATTER == pl->type)
		_draw_scatter_D(ax, pl);
}

t_plot	plot_DV(int size, Vector2 *data)
{
	t_plot	pl;

	pl.points_data = data;
	pl.x_data = NULL;
	pl.y_data = NULL;
	pl.size = size;
	pl.type = DEFAULT_TYPE;
	pl.title = DEFAULT_TITLE;
	pl.color = DEFAULT_COLOR;
	pl.marker_size = DEFAULT_MARKER_SIZE;
	pl.enabled = true;
	return (pl);
}

t_plot	plot_D(int size, float *x, float *y)
{
	t_plot	pl;

	pl.x_data = x;
	pl.y_data = y;
	pl.points_data = NULL;
	pl.size = size;
	pl.type = DEFAULT_TYPE;
	pl.title = DEFAULT_TITLE;
	pl.color = DEFAULT_COLOR;
	pl.marker_size = DEFAULT_MARKER_SIZE;
	pl.enabled = true;
	return (pl);
}

void	plot_destroy(t_plot *pl)
{
	(void)pl;
}
