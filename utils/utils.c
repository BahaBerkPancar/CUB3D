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
			return (NULL);
	}
	board[y] = NULL;
	return (board);
}
