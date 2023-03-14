#ifndef BR_FUNCTION_H
# define BR_FUNCTION_H

# include <stdlib.h>
#include "rayplot.h"

//Broadcast functions over array
float	*brFunctionOverArray(float *x, int size, t_func1 f, float *ret);

//Range functions
float	*ranCreate(Vector3 range);
size_t	ranGetSize(Vector3 range);

#endif
