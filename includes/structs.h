#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

enum e_DIRECTIONS
{
	NORTH,
	SOUTH,
	EASTH,
	WEST,
};

enum e_RGBS
{
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

	int		ceiling_set;
	int		floor_set;
	int		ceiling[3];
	int		floor[3];
	int		rgb_index;
	char	**map;

	int		player_x;
	int		player_y;

}	t_map_data;

#endif 