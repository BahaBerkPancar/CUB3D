#include "cub3d.h"

int	init_data(t_map_data *data)
{
	data->map = NULL;
	data->floor_set = 0;
	data->ceiling_set = 0;
	data->rgb_index = 0;
	data->north_file = NULL;
	data->south_file = NULL;
	data->west_file = NULL;
	data->easth_file = NULL;
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->ceiling[0] = -1;
	data->ceiling[1] = -1;
	data->ceiling[2] = -1;
	return (0);
}

t_map_data	*handle_map(int ac, char **av)
{
	t_map_data	*data;

	if (check_args(ac, av) == 1)
		return (NULL);
	data = malloc(sizeof(t_map_data));
	if (!data)
		return (err_msg("Failed to allocate memory"), NULL);
	if (init_data(data))
		return (free(data), NULL);
	if (read_map(av[1], data) == 1)
		return (free_data(data), NULL);
	return (data);
}

int	main(int ac, char **av)
{
	t_map_data	*data;
	t_window	*mlx;

	data = handle_map(ac, av);
	if (!data || map_checks(data))
		return (free_data(data), 1);
	mlx = init_mlx(data);
	if (!mlx)
		return (free_data(data), 1);
	free_data(data);
	start_window(mlx);
	clean_mlx(mlx);
	return (printf("Map read successfully\n"), 0);
}
