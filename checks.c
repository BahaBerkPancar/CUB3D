#include "cub3d.h"

int	check_file(char *map_file)
{
	int		fd;
	char	c;
	
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return ft_putstr_fd("Error: Failed to open file\n", 2), 1;
	if (read(fd, &c, 1) <= 0)
		return ft_putstr_fd("Error: empty file\n", 2), close(fd), 1;
	close(fd);
	return 0;
}


int	check_map(int ac, char **av)
{
	char	*map_file;
	
	if (ac != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	map_file = ft_strdup(av[1]);
	ft_strrev(map_file);
	if (ft_strncmp(map_file, "buc.", 4) != 0)
		return (free(map_file), ft_putstr_fd("Error: Invalid map file\n", 2), 1);
	ft_strrev(map_file);
	if (check_file(map_file) == 1)
		return (free(map_file), 1);
	return (free(map_file), 0);
}
