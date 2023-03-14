#include "csv.h"

size_t	csvGetSize(const char * filename)
{
	FILE	*fd = fopen(filename, "r");
	char	*str = NULL;
	size_t	len, i;
	for (i = 0; EOF != getline(&str, &len, fd); i++);
	fclose(fd);
	return i;
}

Vector2	*csvReadV2(const char * filename)
{
	size_t	len;
	Vector2	*ret = NULL;
	char	*str = NULL;
	char	*spl = NULL;
	FILE	*fd = fopen(filename, "r");

	ret = (Vector2 *)malloc(sizeof(Vector2) * csvGetSize(filename));

	fd = fopen(filename, "r");
	for (int i = 0; EOF != getline(&str, &len, fd); i++)
	{
		spl = strtok(str, ",");
		ret[i].x = atof(spl);
		spl = strtok(NULL, ",");
		ret[i].y = atof(spl);
	}
	fclose(fd);
	return (ret);
}

void	csvWriteV2(const char * filename, Vector2 *v, int size)
{
	(void)v;
	FILE	*fd = fopen(filename, "w");

	for (int i = 0; i < size; i++)
		fprintf(fd, "%f, %f\n", v[i].x, v[i].y);
}

void	csvWrite2(const char * filename, float *x, float *y, int size)
{
	FILE	*fd = fopen(filename, "w");

	for (int i = 0; i < size; i++)
		fprintf(fd, "%f, %f\n", x[i], y[i]);
}
