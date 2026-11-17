#include "../includes/cub3d.h"

void	set_mlx_ints(t_window	*mlx, t_map_data *data)
{
	mlx->map_height = 0;
	mlx->map_width = ft_strlen(data->map[0]);
	while (data->map[mlx->map_height])
		mlx->map_height++;
	mlx->img_height = 16;
	mlx->img_width = 16;
	mlx->move_backward = 0;
	mlx->move_forward = 0;
	mlx->move_left = 0;
	mlx->move_right = 0;
	mlx->show_minimap = 0;
	mlx->win_height = 600;
	mlx->win_width = 800;
	mlx->tile_size = 10;
	mlx->ceiling[0] = data->ceiling[0];
	mlx->ceiling[1] = data->ceiling[1];
	mlx->ceiling[2] = data->ceiling[2];
	mlx->floor[0] = data->floor[0];
	mlx->floor[1] = data->floor[1];
	mlx->floor[2] = data->floor[2];
	if (mlx->map_height * mlx->tile_size > mlx->win_height)
		mlx->tile_size = mlx->win_height / mlx->map_height;
}

t_window	*init_mlx(t_map_data *data)
{
	t_window	*mlx;

	mlx = malloc(sizeof(t_window));
	if (!mlx)
		return (err_msg("Malloc Failure"), NULL);
	ft_bzero(mlx, sizeof(t_window));
	set_mlx_ints(mlx, data);
	mlx->map = copy_map(data, mlx);
	if (!mlx->map)
		return (free(mlx), err_msg("Map copy failed"), NULL);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (clean_mlx(mlx), NULL);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->win_width, mlx->win_height, "cub3D");
	if (!mlx->win_ptr)
		return (clean_mlx(mlx), NULL);
	if (create_xpm_image(mlx, data) || create_frame(mlx))
		return (clean_mlx(mlx), NULL);
	init_player(mlx);
	return (mlx);
}

int	load_texture(t_window *mlx, t_texture *tex, char *file, char *msg)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx_ptr, file,
			&tex->width, &tex->height);
	if (!tex->img)
		return (err_msg(msg), 1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (0);
}

int	create_xpm_image(t_window *mlx, t_map_data *data)
{
	if (load_texture(mlx, &mlx->easth, data->easth_file,
			"Problem creating east xpm"))
		return (1);
	mlx->easth_xpm = mlx->easth.img;
	if (load_texture(mlx, &mlx->west, data->west_file,
			"Problem creating west xpm"))
		return (1);
	mlx->west_xpm = mlx->west.img;
	if (load_texture(mlx, &mlx->north, data->north_file,
			"Problem creating north xpm"))
		return (1);
	mlx->north_xpm = mlx->north.img;
	if (load_texture(mlx, &mlx->south, data->south_file,
			"Problem creating south xpm"))
		return (1);
	mlx->south_xpm = mlx->south.img;
	return (0);
}

int	create_frame(t_window *mlx)
{
	mlx->img = mlx_new_image(mlx->mlx_ptr, mlx->win_width, mlx->win_height);
	if (!mlx->img)
		return (err_msg("Problem creating frame image"), 1);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	return (0);
}
