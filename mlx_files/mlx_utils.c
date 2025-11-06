#include "../includes/cub3d.h"

void	draw_square(t_window *mlx, int start_x, int start_y, int size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	print_minimap(t_window *mlx)
{
	int		tile_w;
	int		tile_h;
	int		y;
	int		x;
	char	c;

	y = 0;
	tile_h = mlx->win_height / mlx->map_height;
	tile_w = mlx->win_width / mlx->map_width;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			c = mlx->map[y][x];
			if (c == '1')
				draw_square(mlx, x * tile_w, y * tile_h, tile_w, 0xFF0000); // red
			else if (c == '0' || c == ' ')
				draw_square(mlx, x * tile_w, y * tile_h, tile_w, 0x000000); // black
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				draw_square(mlx, x * tile_w, y * tile_h, tile_w, 0xFFFFFF); // white (player)
			x++;
		}
		y++;
	}
}

void	set_mlx_ints(t_window	*mlx, t_map_data *data)
{
	mlx->map_height = 0;
	mlx->map_width = ft_strlen(data->map[0]);
	while (data->map[mlx->map_height])
		mlx->map_height++;
	mlx->img_height = 16;
	mlx->img_width = 16;
	mlx->move_down = 0;
	mlx->move_forward = 0;
	mlx->move_left = 0;
	mlx->move_right = 0;
	mlx->show_minimap = 0;
	mlx->win_height = 600;
	mlx->win_width = 800;
}

t_window	*init_mlx(t_map_data *data)
{
	t_window	*mlx;

	mlx = malloc(sizeof(t_window));
	if (!mlx)
		return (err_msg("Malloc Failure"), NULL);
	set_mlx_ints(mlx, data);
	mlx->map = copy_map(data, mlx);
	if (!mlx->map)
		return (free(mlx), err_msg("Map copy failed"), NULL);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (free(mlx), NULL);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->win_width, mlx->win_height, "cub3D");
	if (!mlx->win_ptr)
		return (clean_mlx(mlx), NULL);
	if (create_xpm_image(mlx, data))
		return (clean_mlx(mlx), NULL);
	return (mlx);
}

int	create_xpm_image(t_window *mlx, t_map_data *data)
{
	mlx->easth_xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, data->easth_file, &mlx->img_width, &mlx->img_height);
	if (!mlx->easth_xpm)
		return (err_msg("Problem creating east xpm"), 1);
	mlx->west_xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, data->west_file, &mlx->img_width, &mlx->img_height);
	if (!mlx->west_xpm)
		return (err_msg("Problem creating west xpm"), 1);
	mlx->north_xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, data->north_file, &mlx->img_width, &mlx->img_height);
	if (!mlx->north_xpm)
		return (err_msg("Problem creating north xpm"), 1);
	mlx->south_xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, data->south_file, &mlx->img_width, &mlx->img_height);
	if (!mlx->south_xpm)
		return (err_msg("Problem creating south xpm"), 1);
	return (0);
}

int	put_image_to_window(t_window *mlx)// this will completely change it is just to test
{
	void	*images[4];
	int		x;
	int		y;
	int		i;

	images[0] = mlx->north_xpm;
	images[1] = mlx->south_xpm;
	images[2] = mlx->easth_xpm;
	images[3] = mlx->west_xpm;
	x = 0;
	y = 0;
	i = 0;
	while (i < 4)
	{
		if (images[i])
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, images[i], x, y);
			x += mlx->img_width;
			if (x + mlx->img_width > mlx->win_width)
			{
				x = 0;
				y += mlx->img_height;
			}
		}
		i++;
	}
	return (0);
}

void	start_window(t_window *mlx)
{
	put_image_to_window(mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, handle_keypress, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, handle_keyrelease, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, handle_close, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update_game, mlx);
	mlx_loop(mlx->mlx_ptr);
}
