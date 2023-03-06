#ifndef PLOT_H
# define PLOT_H
# include "raylib.h"
# include "types.h"
# include "axis.h"

void	plot_lines_D(t_axis2D ax, Vector2 *data, int size, Color col);
void	plot_scatter_D(t_axis2D ax, Vector2 *data, int size, Color col);
//TODO version with static vars to make plots faster?
void	plot_lines_F(t_axis2D ax, double (*f)(double), Vector3 range, Color col);
void	plot_scatter_F(t_axis2D ax, float (*f)(float), Vector2 range);

#endif
