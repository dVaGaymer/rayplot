# include "br_function.h"

float	*br_func(float *x, int size, t_func1 f, float *ret)
{
	for (int i = 0; i < size; i++)
		ret[i] = f(x[i]);
	return ret;
}

float	*create_range(Vector3 range)
{
	int		size = (range.z - range.x) / range.y;
	float	*ret = (float *)malloc(sizeof(float) * size);
	float	num = range.x;

	for (int i = 0; i < size; i++, num += range.y)
		ret[i] = num;
	return ret;
}
