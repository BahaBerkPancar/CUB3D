#include "../includes/cub3d.h"

int	check_file(char *map_file)
{
	int		fd;
	char	c;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (err_msg("Failed to open file"), 1);
	if (read(fd, &c, 1) <= 0)
		return (err_msg("empty file"), close(fd), 1);
	close(fd);
	return (0);
}

int	check_args(int ac, char **av)
{
	char	*map_file;

	if (ac != 2)
		return (err_msg("Invalid number of arguments"), 1);
	map_file = ft_strdup(av[1]);
	ft_strrev(map_file);
	if (ft_strncmp(map_file, "buc.", 4) != 0)
		return (free(map_file), err_msg("Invalid map file"), 1);
	ft_strrev(map_file);
	if (check_file(map_file) == 1)
		return (free(map_file), 1);
	return (free(map_file), 0);
}

int	check_headers(t_map_data *data)
{
	if (data->north_file == NULL || data->south_file == NULL
		|| data->west_file == NULL || data->easth_file == NULL)
		return (err_msg("Missing Textures"), 1);
	if (!data->floor_set || !data->ceiling_set)
		return (err_msg("Missing Colors"), 1);
	if (data->floor[0] == -1 || data->floor[1] == -1 || data->floor[2] == -1
		|| data->ceiling[0] == -1 || data->ceiling[1] == -1
		|| data->ceiling[2] == -1)
		return (err_msg("Missing Colors"), 1);
	return (0);
}
