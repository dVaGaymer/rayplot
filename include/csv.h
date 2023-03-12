#ifndef CSV_H
# define CSV_H

#include "raylib.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector2	*csv_readV2(const char * filename);

#endif
