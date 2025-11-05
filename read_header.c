#include "cub3d.h"

static int	handle_header(char *line, t_map_data *data,
	int *textures, int *colors)
{
	char	*dup;

	if (!line)
		return (1);
	if (is_valid_direction(line))
	{
		if (check_textures(line, data))
			return (1);
		(*textures)++;
	}
	else if (line[0] == 'F' || line[0] == 'C')
	{
		dup = ft_strdup(line);
		if (!dup || check_first_line(dup, data))
			return (free(dup), 1);
		free(dup);
		(*colors)++;
	}
	else
		return (err_msg("Unknown header"), 1);
	return (0);
}

static char	*read_next_line(char *line, int fd)
{
	free(line);
	line = get_next_line(fd);
	return (line);
}

char	*read_headers(char *line, int fd, t_map_data *data)
{
	int	textures;
	int	colors;
	int	i;

	textures = 0;
	colors = 0;
	while (line)
	{
		i = 0;
		while (line[i] && my_isspace(line[i]))
			i++;
		if (!line[i])
		{
			line = read_next_line(line, fd);
			continue ;
		}
		if (line[i] == '1' || line[i] == '0')
			return (line);
		if (handle_header(&line[i], data, &textures, &colors))
			return (free(line), NULL);
		if (textures == 4 && colors == 2)
			return (free(line), skip_empty_lines(fd));
		line = read_next_line(line, fd);
	}
	return (err_msg("Missing Textures or Colors"), NULL);
}
