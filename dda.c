#include "includes/cub3d.h"

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		side;
}	t_dda;

static void	set_step_and_side_dist(t_window *win, double ray_dir_x,
	double ray_dir_y, t_dda *dda)
{
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (win->player.x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - win->player.x)
			* dda->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (win->player.y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - win->player.y)
			* dda->delta_dist_y;
	}
}

static void	perform_dda_loop(t_window *win, double ray_dir_x,
	double ray_dir_y, t_dda *dda)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = WEST;
			if (ray_dir_x < 0)
				dda->side = EASTH;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = NORTH;
			if (ray_dir_y < 0)
				dda->side = SOUTH;
		}
		if (win->map[dda->map_y][dda->map_x] == '1')
			hit = 1;
	}
}

static double	calc_perp_dist(t_window *win, double ray_dir_x,
	double ray_dir_y, t_dda *dda, double *hit_x)
{
	double	perp_wall_dist;
	double	wall_x;

	if (dda->side == WEST || dda->side == EASTH)
		perp_wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		perp_wall_dist = dda->side_dist_y - dda->delta_dist_y;
	if (dda->side == WEST || dda->side == EASTH)
		wall_x = win->player.y + perp_wall_dist * ray_dir_y;
	else
		wall_x = win->player.x + perp_wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	if (dda->side == WEST || dda->side == SOUTH)
		wall_x = 1.0 - wall_x;
	*hit_x = wall_x;
	return (perp_wall_dist);
}

double	perform_dda(t_window *win, double ray_dir_x, double ray_dir_y,
	int *side, double *hit_x)
{
	t_dda	dda;

	dda.map_x = (int)win->player.x;
	dda.map_y = (int)win->player.y;
	dda.delta_dist_x = fabs(1 / ray_dir_x);
	dda.delta_dist_y = fabs(1 / ray_dir_y);
	set_step_and_side_dist(win, ray_dir_x, ray_dir_y, &dda);
	perform_dda_loop(win, ray_dir_x, ray_dir_y, &dda);
	*side = dda.side;
	return (calc_perp_dist(win, ray_dir_x, ray_dir_y, &dda, hit_x));
}
