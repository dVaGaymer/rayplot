#ifndef TYPES_H
# define TYPES_H

# include "raylib.h"
# include "macro.h"

typedef double (*t_func1)(double);

typedef enum	e_line_type
{
	SOLID = 0,
	DOTTED,
	SCATTER
}				t_line_type;

typedef struct	s_plot
{
	Vector2	*data;
	t_func1	func;

	t_line_type	type;
	Color		color;
	char		*title;
}				t_plot;

typedef struct	s_axis2D
{
/*	V2	*/
/*------------------------------------------------------------------------------------*/
	//Axis title and labels
	char	*title;
	int		title_text_size;
	Color	title_text_color; Font	title_text_font;

	char	*x_label;
	int		x_label_text_size;
	Color	x_label_text_color; Font	x_label_text_font;

	char	*y_label;
	int		y_label_text_size;
	Color	y_label_text_color; Font	y_label_text_font;

	// Position and Size
	Rectangle	bounds;
	//What is consider as (0, 0) when drawing the axis to screen
	Vector2		origin;

	// Axis num range
	Vector2	x_range;
	Vector2	y_range;

	// Amount of grid lines for each axis -----> 0 for no grid
	int		x_grid;
	Color	x_grid_color;
	int		y_grid;
	Color	y_grid_color;
	//Choose whether the grid is labeled with its num. values
	bool	grid_num;
	Color	grid_num_color;

	//whether the axis include a legend of its plots
	bool	legend;

	t_plot		plots[MAX_NUMBER_OF_PLOTS];
/*------------------------------------------------------------------------------------*/
}				t_axis2D;

#endif
