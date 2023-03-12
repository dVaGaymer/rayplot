#ifndef CSV_H
# define CSV_H

#include "raylib.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	csv_get_size(const char * filename);

Vector2	*csv_readV2(const char * filename);
void	csv_writeV2(const char * filename, Vector2 *v, int size);
void	csv_write2(const char * filename, float *x, float *y, int size);

#endif
