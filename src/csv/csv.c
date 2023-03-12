#include "csv.h"

Vector2	*csv_readV2(const char * filename)
{
	Vector2	*ret = NULL;
	size_t	len, i;
	char	*str = NULL;
	char	*spl = NULL;
	FILE	*fd = fopen(filename, "r");

	for (i = 0; EOF != getline(&str, &len, fd); i++);
	ret = (Vector2 *)malloc(sizeof(Vector2) * i);
	fclose(fd);

	fd = fopen(filename, "r");
	for (i = 0; EOF != getline(&str, &len, fd); i++)
	{
		spl = strtok(str, ",");
		ret[i].x = atof(spl);
		spl = strtok(NULL, ",");
		ret[i].y = atof(spl);
	}
	fclose(fd);
	return (ret);
}

void	csv_writeV2(const char * filename, Vector2 *v)
{
	(void)filename;
	(void)v;
}

void	csv_write2(const char * filename, float *x, float *y)
{
	(void)filename;
	(void)x;
	(void)y;
}
