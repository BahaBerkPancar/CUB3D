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
	RED,
	GREEN,
	BLUE,
	FLOOR,
	CEILING,
};


typedef struct s_map_data
{
	char	*north_xpm;
	char	*easth_xpm;
	char	*west_xpm;
	char	*south_xpm;

	int		ceiling[3];
	int		floor[3];

	char	*map;

}	t_map_data;


#endif 