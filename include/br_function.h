#ifndef BR_FUNCTION_H
# define BR_FUNCTION_H

# include <stdlib.h>
#include "rayplot.h"

float	*br_func(float *x, int size, t_func1 f, float *ret);
float	*create_range(Vector3 range);

#endif
