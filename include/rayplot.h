#ifndef TYPES_H
# define TYPES_H

# include "raylib.h"
# include "macro.h"

typedef void (*t_plotdelfunc)(void *);
typedef double (*t_func1)(double);

typedef enum	e_line_type
{
	SOLID = 0,
	DOTTED,
	SCATTER
}				t_line_type;

//User can set a flag inside plot
//	to tell it is given the responsability to free the data
typedef struct	s_plot
{
	int			plot_id;
	Vector2		*points_data;
	float		*x_data;
	float		*y_data;
	int			size;

	t_line_type	type;
	Color		color;
	char		*title;
	float		marker_size;

	bool		enabled;
}				t_plot;

typedef struct	s_axis2D
{
	// Position
	Rectangle	bounds;
	Vector2		origin;
	//Axis title and labels
	char		*title;
	int			title_text_size;
	Color		title_text_color; Font	title_text_font;
	//X label
	char		*x_label;
	int			x_label_text_size;
	Color		x_label_text_color; Font	x_label_text_font;
	//Y label
	char		*y_label;
	int			y_label_text_size;
	Color		y_label_text_color; Font	y_label_text_font;

	//Whether the graph has inner or outter frame
	float	inner_frame;
	float	outter_frame;
	//Distance between inner and outter frame
	int			padding;

	// Axis num range
	Vector3		x_range;
	Vector3		y_range;

	// Amount of grid lines for each axis -----> 0 for no grid
	int			x_grid;
	Color		x_grid_color;
	int			y_grid;
	Color		y_grid_color;

	//Choose whether the grid is labeled with its num. values
	int			x_grid_num;
	int			y_grid_num;
	Color		grid_num_text_color;
	int			grid_num_text_size; Font	grid_num_text_font;
	float		x_grid_thickness;
	float		y_grid_thickness;

	//whether the axis include a legend of its plots
	bool		legend;
	float		legend_text_size;

	int			plots_size;
	t_plot		plots[MAX_NUMBER_OF_PLOTS];
}				t_axis2D;

//------- PLOT -------
/**
 * @brief  Draws plot pl from axis ax.
 *
 * @details
 * It is called by axis_show, but can be called independently
 *
 * @param ax Axis
 * @param id id of a plot inside ax
 */
void	plot_draw(t_axis2D const *ax, int id);
/**
 * @brief
 * Creates a plot from two arrays of data.
 *
 * @details
 * Data is stored as a shallow copy so the user can animate it.
 *
 * Is the user job to handle (free) the data.
 *
 * Both data sets must have the same size.
 *
 * @param size Size of BOTH data set
 * @param x
 * @param y
 * @return t_plot
 */
t_plot	plot_D(int size, float *x, float *y);
/**
 * @brief Creates a plot from an array of points
 *
 * @param size Size of the vector array
 * @param data
 * @return t_plot
 */
t_plot	plot_DV(int size, Vector2 *data);
//TODO: Think of a destruction function
void	plot_destroy(t_plot *pl);

//------ AXIS ------
Vector2		axis_map_to_screen(t_axis2D const *ax, Vector2 p); //const | does not change axis
t_axis2D	*axis_create(t_axis2D *ax, Rectangle bounds);
void		axis_show(t_axis2D const *ax); //const | does not change axis
void		axis_destroy(t_axis2D *ax, t_plotdelfunc f);
void		axis_add_plot(t_axis2D *ax, t_plot pl);

#endif
