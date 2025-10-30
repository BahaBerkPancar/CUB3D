#include "cub3d.h"

int	handle_map(int ac, char **av)
{
	t_map_data	*data;

	if (check_map(ac, av) == 1)
		return (1);
	data = malloc(sizeof(t_map_data));
	if (read_map(av[1], data) == 1)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	if (handle_map(ac, av) == 1)
		return (1);
	
	printf("Map read successfully\n");
	return (0);
}