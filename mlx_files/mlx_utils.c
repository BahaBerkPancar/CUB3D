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
	if (mlx->map_height * mlx->tile_size > mlx->win_height)
		mlx->tile_size = mlx->win_height / mlx->map_height;
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
		return (clean_mlx(mlx), NULL);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->win_width, mlx->win_height, "cub3D");
	if (!mlx->win_ptr)
		return (clean_mlx(mlx), NULL);
	if (create_xpm_image(mlx, data))
		return (clean_mlx(mlx), NULL);
	init_player(mlx);
	return (mlx);
}

int	create_xpm_image(t_window *mlx, t_map_data *data)
{
	mlx->easth_xpm = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->easth_file, &mlx->img_width, &mlx->img_height);
	if (!mlx->easth_xpm)
		return (err_msg("Problem creating east xpm"), 1);
	mlx->west_xpm = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->west_file, &mlx->img_width, &mlx->img_height);
	if (!mlx->west_xpm)
		return (err_msg("Problem creating west xpm"), 1);
	mlx->north_xpm = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->north_file, &mlx->img_width, &mlx->img_height);
	if (!mlx->north_xpm)
		return (err_msg("Problem creating north xpm"), 1);
	mlx->south_xpm = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->south_file, &mlx->img_width, &mlx->img_height);
	if (!mlx->south_xpm)
		return (err_msg("Problem creating south xpm"), 1);
	return (0);
}
