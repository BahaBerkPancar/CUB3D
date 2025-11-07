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

typedef struct s_player
{
	double	x;
	double	y;

	double	dir_x;
	double	dir_y;

	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_map_data
{
	char		*north_file;
	char		*easth_file;
	char		*west_file;
	char		*south_file;

	int			ceiling_set;
	int			floor_set;
	int			rgb_index;
	int			ceiling[3];
	int			floor[3];
	char		**map;
	int			player_x;
	int			player_y;

}	t_map_data;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;

	char		**map;
	//xpms
	void		*north_xpm;
	void		*easth_xpm;
	void		*west_xpm;
	void		*south_xpm;

	//sizes	
	int			img_width;
	int			img_height;
	int			win_width;
	int			win_height;
	int			map_width;
	int			map_height;
	int			tile_size;

	//movement flags
	int			move_forward;
	int			move_backward;
	int			move_left;
	int			move_right;
	int			show_minimap;
	int			rotate_left;
	int			rotate_right;

	// rgbs
	int			ceiling[3];
	int			floor[3];

	//starting positions
	int			player_start_x;
	int			player_start_y;
	int			player_start_dir_x;
	int			player_start_dir_y;
	t_player	player;
}	t_window;

#endif