#ifndef BR_FUNCTION_H
# define BR_FUNCTION_H

# include <stdlib.h>
#include "rayplot.h"

float	*br_func(float *x, int size, t_func1 f, float *ret);
float	*range_create(Vector3 range);
size_t	range_size(Vector3 range);

#endif
