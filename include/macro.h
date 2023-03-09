#ifndef MACRO_H
# define MACRO_H

# define WIDTH 1200.0f
# define HEIGHT 800.0f
# ifndef NULL
#  define NULL (void *)0
# endif

# define MAX_NUMBER_OF_PLOTS 16
# define INITIAL_PLOT_SIZE 0
# define DEFAULT_STEPS 0.1
# define DEFAULT_COLOR BLACK
# define DEFAULT_MARKER_SIZE 2

# define DEFAULT_INNER_FRAME_THICKNESS 2
# define DEFAULT_OUTTER_FRAME_THICKNESS 0
# define DEFAULT_X_GRID_THICKNESS 1
# define DEFAULT_Y_GRID_THICKNESS 1

# define DEFAULT_X_GRID 3
# define DEFAULT_Y_GRID 3

# define SPACING 3
# define NO_PADDING 0
# define DEFAULT_PADDING 0.25 * (bounds.height < bounds.width ? bounds.height : bounds.width)
# define DECIMAL_FORMAT "%.1f"

# define DEFAULT_FONT GetFontDefault();
# define DEFAULT_TITLE_TEXT_SIZE 30
# define DEFAULT_LABEL_TEXT_SIZE 20
# define DEFAULT_GRID_NUM_TEXT_SIZE 10

# define DEFAULT_LEGEND_TEXT_SIZE 10
# define DEFAULT_LEGEND_COLOR WHITE
# define DEFAULT_LEGEND_HEIGHT 0.25 * ax->bounds.height
# define DEFAULT_LEGEND_WIDTH 0.2 * ax->bounds.width

# define NULL_VECTOR3 (Vector3){0,0,0}
# define DEFAULT_ORIGIN {0.5f, 0.5f}
# define DEFAULT_X_RANGE {-1, 0.1, 1}
# define DEFAULT_Y_RANGE {-1, 0.1, 1}


# define NO_ROTATION 0
# define DEG_ACW_90_ROTATION -90

#endif
