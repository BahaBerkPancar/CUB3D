#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

enum DIRECTIONS{
	NORTH,
	SOUTH,
	EASTH,
	WEST,
};
enum RGBS{
	FLOOR,
	CEILING,
};

typedef struct s_map_data
{
	char	*north_xpm;
	char	*easth_xpm;
	char	*west_xpm;
	char	*south_xpm;

	char	*ceiling;
	char	*floor;

	char	*map;

}	t_map_data;


#endif 