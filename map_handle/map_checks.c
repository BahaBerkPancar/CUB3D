#include "../includes/cub3d.h"

int	normalize_map(t_map_data *data)
{
	char	**new;
	size_t	max;
	int		y;
	int		x;

	max = get_max_width(data->map);
	y = 0;
	while (data->map[y])
		y++;
	new = malloc(sizeof(char *) * (y + 1));
	y = -1;
	while (data->map[++y])
	{
		new[y] = malloc(max + 1);
		x = -1;
		while (data->map[y][++x])
			new[y][x] = data->map[y][x];
		while (x < (int)max)
			new[y][x++] = ' ';
		new[y][x] = '\0';
	}
	new[y] = NULL;
	free_pointer((void **)data->map);
	data->map = new;
	return (0);
}

int	check_disconnected_map(t_map_data *data, int player_y, int player_x)
{
	int	x;
	int	y;
	int	**board;

	board = change_to_int(data->map);
	if (!board)
		return (err_msg("Malloc failed"), 1);
	flood_fill(data->map, player_y, player_x, board);
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
			if (ft_strchr("0NSEW1", data->map[y][x]) && !board[y][x])
				return (free_pointer((void **)board),
					err_msg("Map has disconnected Area"), 1);
	}
	return (free_pointer((void **)board), 0);
}

int	check_invalid_chars(t_map_data *data)
{
	int		x;
	int		y;
	char	**m;

	m = data->map;
	y = 0;
	while (m && m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] != '0' && m[y][x] != '1' && m[y][x] != ' ' &&
				m[y][x] != 'N' && m[y][x] != 'S' &&
				m[y][x] != 'E' && m[y][x] != 'W' && m[y][x] != '\n')
				return (err_msg("Invalid character in map"), 1);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_open_map(t_map_data *data)
{
	int		x;
	int		y;
	char	**m;

	m = data->map;
	y = 0;
	while (m && m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] == '0' || m[y][x] == 'N'
				|| m[y][x] == 'S' || m[y][x] == 'E' || m[y][x] == 'W')
			{
				if (y == 0 || !m[y + 1] || x == 0
					|| !m[y][x + 1] || !m[y - 1][x] || !m[y + 1][x]
					|| m[y][x - 1] == ' ' || m[y][x + 1] == ' '
					|| m[y - 1][x] == ' ' || m[y + 1][x] == ' ')
					return (err_msg("Map not closed"), 1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_player(t_map_data *data)
{
	int		x;
	int		y;
	char	**m;
	int		count;

	m = data->map;
	y = -1;
	count = 0;
	while (m && m[++y])
	{
		x = -1;
		while (m[y][++x])
		{
			if (m[y][x] == 'N' || m[y][x] == 'S'
				|| m[y][x] == 'E' || m[y][x] == 'W')
			{
				data->player_x = x;
				data->player_y = y;
				count++;
			}
		}
	}
	if (count != 1)
		return (err_msg("Wrong Player Count"), 1);
	return (0);
}
