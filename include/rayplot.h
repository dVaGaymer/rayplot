#ifndef TYPES_H
# define TYPES_H

# include "raylib.h"
# include "macro.h"
# include <stdlib.h>

typedef double (*t_func1)(double);

typedef enum	e_line_type
{
	SOLID = 0,
	DOTTED,
	SCATTER
}				t_line_type;

typedef struct	s_plot
{
	int		plot_id;
	Vector2		*data;
	t_func1		func;
	//If data -> size.x = size.y = size.z = size
	//If func -> size.x = left_lim | size.y = step | size.z = right_lim
	Vector3		range;
	int			size;

	t_line_type	type;
	Color		color;
	char		*title;
	float		marker_size;

	bool		enabled;
}				t_plot;

typedef struct	s_axis2D
{
/*	V2	*/
/*------------------------------------------------------------------------------------*/
	//Axis title and labels
	char	*title;
	int		title_text_size;
	Color	title_text_color; Font	title_text_font;

	float	inner_frame;
	float	outter_frame;

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
	Vector3	x_range;
	Vector3	y_range;

	// Amount of grid lines for each axis -----> 0 for no grid
	int		x_grid;
	Color	x_grid_color;
	int		y_grid;
	Color	y_grid_color;
	//Choose whether the grid is labeled with its num. values
	int		x_grid_num;
	int		y_grid_num;
	Color	grid_num_text_color;
	int		grid_num_text_size; Font	grid_num_text_font;
	float	x_grid_thickness;
	float	y_grid_thickness;

	//whether the axis include a legend of its plots
	bool	legend;
	float	legend_text_size;

	int		padding;

	int		plots_size;
	t_plot	plots[MAX_NUMBER_OF_PLOTS];
/*------------------------------------------------------------------------------------*/
}				t_axis2D;

//------- PLOT -------
void	plot(t_axis2D const *ax, t_plot pl); //const | does not change axis
void	plot_update_one(t_axis2D *ax, int id);
t_plot	plot_create_F(Vector3 range, t_func1 f, t_line_type type, char *title, Color col);
t_plot	plot_create_D(int size, Vector2 *data, t_line_type type, char *title, Color col);
void	plot_destroy(t_plot pl);

/* NOT IMPLEMENTED YET */
/* FOLLOWING FUNCTIONS WILL WORK OVER NEWLY CREATED PLOT*/
t_axis2D	plot_lines_D(Vector2 *data, int size, Color col);
t_axis2D	plot_scatter_D(Vector2 *data, int size, int marker_size, Color col);
t_axis2D	plot_lines_F(Vector3 range, double (*f)(double), Color col);
t_axis2D	plot_scatter_F(Vector3 range, double (*f)(double), Color col);

//------ AXIS ------
Vector2		axis_map_to_screen(t_axis2D const *ax, Vector2 p); //const | does not change axis
t_axis2D	*axis_create(t_axis2D *ax, Rectangle bounds);
void		axis_show(t_axis2D const *ax); //const | does not change axis
void		axis_destroy(t_axis2D *ax);
void		axis_add_plot(t_axis2D *ax, t_plot pl);

#endif
