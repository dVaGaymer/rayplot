#ifndef CSV_H
# define CSV_H

#include "raylib.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Get CSV file vector length
 *
 * @param filename
 * @return size_t
 */
size_t	csvGetSize(const char * filename);
/**
 * @brief Read vector from CSV file
 *
 * @param filename
 * @return Vector2* Array of points
 */
Vector2	*csvReadV2(const char * filename);
/**
 * @brief Writes to CSV file from a points array
 *
 * @param filename
 * @param v
 * @param size
 */
void	csvWriteV2(const char * filename, Vector2 *v, int size);
/**
 * @brief Writes to CSV file from two sets of 1D data
 *
 * @param filename
 * @param x
 * @param y
 * @param size Size of BOTH sets
 */
void	csvWrite2(const char * filename, float *x, float *y, int size);

#endif
