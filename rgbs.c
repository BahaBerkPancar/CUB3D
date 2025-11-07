#include "./includes/cub3d.h"

static int	check_rgb_value(char *part)
{
	int	value;

	if (!part || !str_isdigit(part))
		return (1);
	value = ft_atoi(part);
	if (value < 0 || value > 255)
		return (1);
	return (0);
}

static int	save_rgb_value(t_map_data *data, int type, int color, int value)
{
	if (type == FLOOR)
		data->floor[color] = value;
	else if (type == CEILING)
		data->ceiling[color] = value;
	return (0);
}

static int	parse_rgb_part(char *tmp, int **x, t_map_data *data, int type)
{
	int		len;
	char	*substr;
	char	*part;
	int		value;

	if (tmp[*x[0]] == ',')
		len = *x[0] - *x[1];
	else
		len = *x[0] - *x[1] + 1;
	substr = ft_substr(tmp, *x[1], len);
	if (!substr)
		return (1);
	part = ft_strtrim(substr, " \n\r\t");
	free(substr);
	if (!part || check_rgb_value(part))
		return (free(part), 1);
	value = ft_atoi(part);
	free(part);
	save_rgb_value(data, type, data->rgb_index, value);
	data->rgb_index++;
	if (tmp[*x[0]] == ',' && tmp[*x[0] + 1] == '\0')
		return (1);
	*x[1] = *x[0] + 1;
	return (0);
}

static int	save_rgbs(char *line, t_map_data *data, int type)
{
	int		i;
	int		j;
	int		*x[2];
	char	*tmp;

	i = -1;
	j = 0;
	data->rgb_index = 0;
	tmp = ft_strdup(line);
	if (!tmp)
		return (1);
	x[0] = &i;
	x[1] = &j;
	while (tmp[++i])
	{
		if (tmp[i] == ',' || tmp[i + 1] == '\0')
		{
			if (parse_rgb_part(tmp, x, data, type))
				return (free(tmp), 1);
		}
	}
	if (data->rgb_index != 3)
		return (free(tmp), 1);
	return (free(tmp), 0);
}

int	check_first_line(char *first_line, t_map_data *data)
{
	char	*trimmed;

	if (first_line[1] != ' ' && first_line[1] != '	')
		return (err_msg("Invalid RGB Type"), 1);
	trimmed = ft_strtrim(first_line + 1, " \n\r\t");
	if (first_line[0] == 'F')
	{
		data->floor_set = 1;
		if (save_rgbs(trimmed, data, FLOOR))
			return (free(trimmed),
				err_msg("Invalid Floor RGB value"), 1);
	}
	else if (first_line[0] == 'C')
	{
		data->ceiling_set = 1;
		if (save_rgbs(trimmed, data, CEILING))
			return (free(trimmed),
				err_msg("Invalid Ceiling RGB value"), 1);
	}
	return (free(trimmed), 0);
}
