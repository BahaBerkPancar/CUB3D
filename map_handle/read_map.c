#include "../includes/cub3d.h"

static char	**append_line(char **lines, char *line, size_t count)
{
	char	**new;
	char	*dup;
	size_t	i;
	size_t	len;

	new = malloc(sizeof(char *) * (count + 2));
	if (!new)
		return (free(line), free_pointer((void **)lines), NULL);
	i = 0;
	while (i < count)
	{
		new[i] = lines[i];
		i++;
	}
	dup = ft_strdup(line);
	if (dup)
	{
		len = ft_strlen(dup);
		if (len > 0 && dup[len - 1] == '\n')
			dup[len - 1] = '\0';
	}
	new[count] = dup;
	new[count + 1] = NULL;
	return (free(lines), free(line), new);
}

static int	load_map_lines(int fd, char *line, t_map_data *data)
{
	char	**lines;
	size_t	count;

	lines = NULL;
	count = 0;
	while (line)
	{
		lines = append_line(lines, line, count);
		if (!lines)
			return (close(fd), 1);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	data->map = lines;
	if (!data->map || !data->map[0])
		return (1);
	return (0);
}

int	read_map(char *map_file, t_map_data *data)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	line = read_headers(line, fd, data);
	if (check_headers(data) == 1)
		return (close(fd), 1);
	if (!line)
		return (err_msg("Missing Map"), close(fd), 1);
	return (load_map_lines(fd, line, data));
}

// void	trim_map_lines(t_map_data *data)
// {
// 	int		y;
// 	char	*tmp;

// 	y = -1;
// 	while (data->map[++y])
// 	{
// 		tmp = ft_strtrim(data->map[y], " ");
// 		free(data->map[y]);
// 		data->map[y] = tmp;
// 	}
// }

int	map_checks(t_map_data *data)
{
	// trim_map_lines(data);
	if (normalize_map(data))
		return (1);
	if (check_open_map(data))
		return (1);
	if (check_invalid_chars(data))
		return (1);
	if (check_player(data))
		return (1);
	if (check_disconnected_map(data, data->player_y, data->player_x))
		return (1);
	return (0);
}
