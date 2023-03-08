#include "rayplot.h"

static void	_axis_draw_inner_frame(t_axis2D ax)
{
	DrawRectangleLinesEx(ax.bounds, (float)2.0f, WHITE);
}

static void	_axis_draw_outter_frame(t_axis2D ax)
{
	Rectangle	new_bounds = (Rectangle)
	{
		ax.bounds.x - ax.padding / 2,
		ax.bounds.y - ax.padding / 2,
		ax.bounds.width + ax.padding,
		ax.bounds.height + ax.padding
	};
	DrawRectangleLinesEx(new_bounds, (float)2.0f, WHITE);
}

static void	_axis_draw_x_grid(t_axis2D ax)
{
	float	step = (ax.bounds.width) / (ax.x_grid + 1);
	for (float i = ax.bounds.x; i < ax.bounds.x + ax.bounds.width; i += step)
		DrawLineV((Vector2){i, ax.bounds.y}, (Vector2){i, ax.bounds.y + ax.bounds.height}, ax.x_grid_color);
}

static void	_axis_draw_x_grid_num(t_axis2D ax)
{
	float	step = (ax.bounds.width) / (ax.x_grid + 1);
	float	step2 = (ax.x_range.y - ax.x_range.x) / (ax.x_grid + 1);

	for (float i = ax.bounds.x, k = ax.x_range.x; i < ax.bounds.x + ax.bounds.width; i += step, k += step2)
		DrawTextPro(ax.grid_num_text_font, TextFormat(DECIMAL_FORMAT, k),
			(Vector2){i, ax.bounds.y + ax.bounds.height + SPACING},
			(Vector2){0, 0},
			NO_ROTATION,
			ax.grid_num_text_size,
			SPACING,
			ax.grid_num_text_color);
}

static void	_axis_draw_y_grid(t_axis2D ax)
{
	float	step = (ax.bounds.height) / (ax.y_grid + 1);
	for (float i = ax.bounds.y; i < ax.bounds.y + ax.bounds.height; i += step)
		DrawLineV((Vector2){ax.bounds.x, i}, (Vector2){ax.bounds.x + ax.bounds.width, i}, ax.y_grid_color);
}

static void	_axis_draw_y_grid_num(t_axis2D ax)
{
	Vector2	text_dim;

	float	step = (ax.bounds.height) / (ax.y_grid + 1);
	float	step2 = (ax.y_range.y - ax.y_range.x) / (ax.y_grid + 1);

	for (float i = ax.bounds.y, k = ax.y_range.y; i < ax.bounds.y + ax.bounds.height; i += step, k -= step2)
	{
		text_dim = MeasureTextEx(ax.grid_num_text_font, TextFormat(DECIMAL_FORMAT, k), ax.grid_num_text_size, SPACING);
		DrawTextPro(ax.grid_num_text_font, TextFormat(DECIMAL_FORMAT, k),
			(Vector2){ax.bounds.x, i},
			(Vector2){text_dim.x + SPACING, 0},
			NO_ROTATION,
			ax.grid_num_text_size,
			SPACING,
			ax.grid_num_text_color);
	}
}

static void	_axis_draw_title(t_axis2D ax)
{
	Vector2	text_dim;

	text_dim = MeasureTextEx(ax.title_text_font, ax.title, ax.title_text_size, SPACING);
	DrawTextPro(ax.title_text_font, ax.title,
		(Vector2){ax.bounds.x + ax.bounds.width/2, ax.bounds.y},
		(Vector2){text_dim.x/2, text_dim.y},
		NO_ROTATION,
		ax.title_text_size,
		SPACING,
		ax.title_text_color);
}

static void	_axis_draw_x_label(t_axis2D ax)
{
	Vector2	text_dim;

	text_dim = MeasureTextEx(ax.x_label_text_font, ax.x_label, ax.x_label_text_size, SPACING);
	DrawTextPro(ax.x_label_text_font, ax.x_label,
		(Vector2){ax.bounds.x + ax.bounds.width/2, ax.bounds.y + ax.bounds.height + 2 * ax.grid_num_text_size},
		(Vector2){text_dim.x/2, 0},
		NO_ROTATION,
		ax.x_label_text_size,
		SPACING,
		ax.x_label_text_color);
}

static void	_axis_draw_y_label(t_axis2D ax)
{
	Vector2	text_dim;

	text_dim = MeasureTextEx(ax.y_label_text_font, ax.y_label, ax.y_label_text_size, SPACING);
	DrawTextPro(ax.y_label_text_font, ax.y_label,
		(Vector2){ax.bounds.x - 2 * ax.grid_num_text_size, ax.bounds.y + ax.bounds.height/2},
		(Vector2){text_dim.x/2, text_dim.y},
		DEG_ACW_90_ROTATION,
		ax.y_label_text_size,
		SPACING,
		ax.y_label_text_color);
}

/*-------------------------------------------------------*/
void	axis_create(t_axis2D *ax, Rectangle bounds)
{
	ax->padding = DEFAULT_PADDING;

	ax->frame = true;
	ax->bounds = bounds;
	ax->bounds.width -= ax->padding;
	ax->bounds.height -= ax->padding;
	ax->origin = (Vector2)DEFAULT_ORIGIN;
	ax->bounds.x -= ax->origin.x * ax->bounds.width;
	ax->bounds.y -= ax->origin.y * ax->bounds.height;

	ax->x_range = (Vector2)DEFAULT_X_RANGE;
	ax->y_range = (Vector2)DEFAULT_Y_RANGE;

	ax->x_grid = 5;
	ax->x_grid_color = LIGHTGRAY;
	ax->y_grid = 5;
	ax->y_grid_color = LIGHTGRAY;
	ax->x_grid_num = true; ax->y_grid_num = true;
	ax->grid_num_text_size = DEFAULT_GRID_NUM_TEXT_SIZE;
	ax->grid_num_text_color = WHITE; ax->grid_num_text_font = GetFontDefault();

	ax->title = NULL;
	ax->title_text_size = DEFAULT_TITLE_TEXT_SIZE;
	ax->title_text_color = WHITE; ax->title_text_font = GetFontDefault();
	ax->x_label = NULL;
	ax->x_label_text_size = DEFAULT_LABEL_TEXT_SIZE;
	ax->x_label_text_color = WHITE; ax->x_label_text_font = GetFontDefault();
	ax->y_label = NULL;
	ax->y_label_text_size = DEFAULT_LABEL_TEXT_SIZE;
	ax->y_label_text_color = WHITE; ax->y_label_text_font = GetFontDefault();
}

Vector2	axis_map_to_screen(t_axis2D ax, Vector2 p)
{
	Vector2	new_pos = (Vector2)
	{
		ax.bounds.x
			+ (p.x - ax.x_range.x) * ax.bounds.width
			/ (ax.x_range.y - ax.x_range.x),
		ax.bounds.y + ax.bounds.height
			- (p.y - ax.y_range.x) * ax.bounds.height
			/ (ax.y_range.y - ax.y_range.x)
	};
	new_pos.x = new_pos.x < ax.bounds.x ? ax.bounds.x : new_pos.x;
	new_pos.x = new_pos.x > (ax.bounds.x + ax.bounds.width) ? ax.bounds.x + ax.bounds.width : new_pos.x;

	new_pos.y = new_pos.y < ax.bounds.y ? ax.bounds.y : new_pos.y;
	new_pos.y = new_pos.y > (ax.bounds.y + ax.bounds.height) ? ax.bounds.y + ax.bounds.height : new_pos.y;
	return (new_pos);
}

void	axis_show(t_axis2D ax)
{
	_axis_draw_outter_frame(ax);
	if (ax.frame)
		_axis_draw_inner_frame(ax);
	if (ax.x_grid)
		_axis_draw_x_grid(ax);
	if (ax.y_grid)
		_axis_draw_y_grid(ax);
	if (ax.title)
		_axis_draw_title(ax);
	if (ax.x_label)
		_axis_draw_x_label(ax);
	if (ax.y_label)
		_axis_draw_y_label(ax);
	if (ax.x_grid_num)
		_axis_draw_x_grid_num(ax);
	if (ax.x_grid_num)
	_axis_draw_y_grid_num(ax);
}
