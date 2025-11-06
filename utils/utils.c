#include "../includes/cub3d.h"

int	**change_to_int(char **map)
{
	int		**board;
	int		y;
	size_t	len;

	y = 0;
	while (map[y])
		y++;
	board = malloc(sizeof(int *) * (y + 1));
	if (!board)
		return (NULL);
	y = -1;
	while (map[++y])
	{
		len = ft_strlen(map[y]);
		board[y] = ft_calloc(len, sizeof(int));
		if (!board[y])
		{
			while (y--)
				free(board[y]);
			free(board);
			return (NULL);
		}
	}
	board[y] = NULL;
	return (board);
}

size_t	get_max_width(char **map)
{
	size_t	max;
	size_t	len;
	int		i;

	i = 0;
	max = 0;
	while (map && map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	**copy_map(t_map_data *data, t_window *mlx)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (mlx->map_height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < mlx->map_height)
	{
		copy[y] = ft_strdup(data->map[y]);
		if (!copy[y])
		{
			while (y--)
				free(copy[y]);
			free(copy);
			return (NULL);
		}
		y++;
	}
	copy[mlx->map_height] = NULL;
	return (copy);
}
