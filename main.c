#include "cub3d.h"

int	init_data(t_map_data *data)
{
	data->map = NULL;
	data->floor_set = 0;
	data->ceiling_set = 0;
	data->rgb_index = 0;
	data->north_xpm = NULL;
	data->south_xpm = NULL;
	data->west_xpm = NULL;
	data->easth_xpm = NULL;
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

	data = handle_map(ac, av);
	if (!data || map_checks(data))
		return (1);
	print_everything(data);
	free_data(data);
	printf("Map read successfully\n");
	return (0);
}
