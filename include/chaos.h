#ifndef CHAOS_H
# define CHAOS_H

# include "raylib.h"

# define IT 1000

typedef double	(*t_func)(double);

typedef struct	s_ds_1D
{
	float	x_data[IT];
	float	ctrl_param;
	float	x0;
	float	steps;
	t_func	f;
}				t_ds_1D;

/**
 * @brief Fill X array calulating new output using the previous as input
 *
 * @param x Must have 1 real intiial value
 * @param f (double)(*f)(double)
 * @param size size of PREALLOCATED array
 * @return filled x array
 */
float	*rec_func(float *x, t_func f, int size);

#endif
