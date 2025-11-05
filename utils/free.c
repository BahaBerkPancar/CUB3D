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
	if (data->north_xpm)
		free(data->north_xpm);
	if (data->south_xpm)
		free(data->south_xpm);
	if (data->west_xpm)
		free(data->west_xpm);
	if (data->easth_xpm)
		free(data->easth_xpm);
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
