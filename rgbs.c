#include "./includes/cub3d.h"

int	save_rgbs(char *line, t_map_data *data, int type)
{
	int		i;
	int		j;
	int		color;
	char	*tmp;
	char	*result;
	int		len;

	i = -1;
	j = 0;
	color = 0;
	tmp = ft_strdup(line);
	while (tmp[++i])
	{
		if (tmp[i] == ',' || tmp[i + 1] == '\0')
		{
			if (tmp[i] == ',')
				len = i - j;
			else
				len = i - j + 1;
			result = ft_strtrim(ft_substr(tmp, j, len),  " \n\r\t");
			if (result == NULL || !str_isdigit(result))///////////
				return (free(tmp), free(result), 1);
			if (type == FLOOR)
				data->floor[color] = ft_atoi(result);
			else if (type == CEILING)
				data->ceiling[color] = ft_atoi(result);
			free(result);
			color++;
			j = i + 1;
		}
	}
	if (color != 3)
		return (free(tmp), 1);
	return (free(tmp), 0);
}


static int	check_first_line(char *first_line, t_map_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(first_line + 1, " \n\r\t");
	if (first_line[0] == 'F')
	{
		if(save_rgbs(trimmed, data, FLOOR))
			return(ft_putstr_fd("Error: Invalid Floor RGB value\n", 2), 1);
	}
	else if (first_line[0] == 'C')
	{
		if(save_rgbs(trimmed, data, CEILING))
			return(ft_putstr_fd("Error: Invalid Ceiling RGB value\n", 2), 1);
	}
	free(trimmed);
	free(first_line);
	return (0);
}

char	*read_rgbs(char *first_line, int fd, t_map_data *data)
{
	int		i;

	i = 0;
	if(check_first_line(ft_strdup(first_line), data))
		return(free(first_line), NULL);
	free(first_line);
	first_line = get_next_line(fd);
	while (first_line)
	{
		i = 0;
		while (first_line[i] && my_isspace(first_line[i]))
			i++;
		if (!first_line[i])
		{
			free(first_line);
			first_line = get_next_line(fd);
			continue;
		}
		if (first_line[i] == 'W' || first_line[i] == 'S' || first_line[i] == 'N'
			|| first_line[i] == 'E' || first_line[i] == '1' || first_line[i] == '0')
			return(first_line);
		if(check_first_line(ft_strdup(first_line), data))
			return(free(first_line), NULL);
		free(first_line);
		first_line = get_next_line(fd);
	}
	return (free(first_line), NULL);
}
