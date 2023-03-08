# define SPACING 3
# define DEG_ACW_90_ROTATION -90
# define NO_ROTATION 0
# define MAX_NUMBER_OF_PLOTS 16
# define MAX_TEXT_SIZE 64
# define DEFAULT_ORIGIN {0.5f, 0.5f}
# define DEFAULT_X_RANGE {-1, 0.1, 1}
# define DEFAULT_Y_RANGE {-1, 0.1, 1}
# define DEFAULT_LABEL_TEXT_SIZE 0.06 * (ax->bounds.height < ax->bounds.width ? ax->bounds.height : ax->bounds.width)
# define DEFAULT_TITLE_TEXT_SIZE 0.09 * (ax->bounds.height < ax->bounds.width ? ax->bounds.height : ax->bounds.width)
# define DEFAULT_GRID_NUM_TEXT_SIZE 10
# define DEFAULT_PADDING 0.25 * (bounds.height < bounds.width ? bounds.height : bounds.width)
# define NO_PADDING 0
# define DEFAULT_COLOR BLACK
# define DEFAULT_STEPS 0.1
# define DEFAULT_MARKER_SIZE 1.5
# define NULL_VECTOR3 (Vector3){0,0,0}
# define DEFAULT_FONT GetFontDefault();
// # define DEFAULT_FONT LoadFont("/Users/al7aro/Documents/Libraries/raylib/examples/text/resources/fonts/pixelplay.png");

# define DECIMAL_FORMAT "%.1f"
# define DECIMAL_FORMAT_EXAMPLE "0.0"

# ifndef NULL
#  define NULL (void *)0
# endif
