#include "../includes/cub3d.h"

void	free_data(t_map_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	if (data->north_file)
		free(data->north_file);
	if (data->south_file)
		free(data->south_file);
	if (data->west_file)
		free(data->west_file);
	if (data->easth_file)
		free(data->easth_file);
	free(data);
}

void	free_pointer(void **lines)
{
	size_t	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

void	free_4(char *a, char *b, char *c, char *d)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
}

void	clean_mlx(t_window *mlx)
{
	if (!mlx)
		return ;
	if (mlx->map)
		free_pointer((void **)mlx->map);
	if (mlx->north_xpm)
		mlx_destroy_image(mlx->mlx_ptr, mlx->north_xpm);
	if (mlx->easth_xpm)
		mlx_destroy_image(mlx->mlx_ptr, mlx->easth_xpm);
	if (mlx->west_xpm)
		mlx_destroy_image(mlx->mlx_ptr, mlx->west_xpm);
	if (mlx->south_xpm)
		mlx_destroy_image(mlx->mlx_ptr, mlx->south_xpm);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	free(mlx);
}
