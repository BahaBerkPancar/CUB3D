#include "includes/cub3d.h"

typedef struct s_render
{
	int		x;
	int		start;
	int		end;
	int		height;
	double	hit_x;
}	t_render;

void	draw_vertical_stripe(t_window *win, t_render *r, t_texture *tex)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (int)(r->hit_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	y = -1;
	while (++y < win->win_height)
	{
		if (y < r->start)
			color = rgb_to_int(win->ceiling);
		else if (y > r->end)
			color = rgb_to_int(win->floor);
		else
		{
			tex_y = ((y - r->start) * tex->height) / r->height;
			color = get_texture_pixel(tex, tex_x, tex_y);
		}
		put_pixel(win, r->x, y, color);
	}
}

void	set_texture(t_window *win, t_texture **tex, int side)
{
	if (side == NORTH)
		*tex = &win->north;
	else if (side == SOUTH)
		*tex = &win->south;
	else if (side == WEST)
		*tex = &win->west;
	else
		*tex = &win->easth;
}

void	cast_ray(t_window *win, t_render *r, t_texture **tex)
{
	double	ray_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	double	dist_to_wall;
	int		side;

	ray_angle = (r->x - win->win_width / 2.0) * (M_PI / 3) / win->win_width;
	ray_dir_x = win->player.dir_x * cos(ray_angle)
		- win->player.dir_y * sin(ray_angle);
	ray_dir_y = win->player.dir_x * sin(ray_angle)
		+ win->player.dir_y * cos(ray_angle);
	dist_to_wall = perform_dda(win, ray_dir_x, ray_dir_y, &side, &r->hit_x);
	if (dist_to_wall < 0.0001)
		dist_to_wall = 0.0001;
	r->height = (int)(win->win_height / dist_to_wall);
	if (r->height < 1)
		r->height = 1;
	r->start = win->win_height / 2 - r->height / 2;
	r->end = win->win_height / 2 + r->height / 2;
	set_texture(win, tex, side);
}

void	render_frame(t_window *win)
{
	t_texture	*tex;
	t_render	r;

	r.x = -1;
	while (++r.x < win->win_width)
	{
		cast_ray(win, &r, &tex);
		draw_vertical_stripe(win, &r, tex);
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img, 0, 0);
}
