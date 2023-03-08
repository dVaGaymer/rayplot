#ifndef hooke_H
# define hooke_H
#include "raylib.h"
# include <math.h>
# include "macro.h"
#include <stdlib.h>

typedef struct	s_hooke
{
	float	k;
	float	m;
	float	d_t;
	float	t;
	float	x0;
	float	v0;

	float	x;
	Vector2	*data;
	Vector2	*vel_data;
	int		steps;
}				t_hooke;

void	hooke_reset(t_hooke *h, float k, float m, float t, float x0, float v);
void	hooke_init(t_hooke *h, int steps);
void	hooke_destroy(t_hooke *h);
void	hooke_set_k(t_hooke *h, float k);
void	hooke_set_m(t_hooke *h, float m);
void	hooke_set_x0(t_hooke *h, float x0);
float	hooke_get_period(t_hooke h);
void	hooke_vel_data(t_hooke *h);

#endif
