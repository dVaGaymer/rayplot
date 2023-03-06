#ifndef AXIS_H
# define AXIS_H
# include "raylib.h"
# include "types.h"
# include "plot.h"
# include <string.h>
# include <stdlib.h>

//TODO SCALE MAP TO SCREEN
Vector2	axis_map_to_screen(t_axis2D ax, float x, float y);
void	axis_create(t_axis2D *ax, Rectangle bounds);
void	axis_show(t_axis2D ax);

#endif
