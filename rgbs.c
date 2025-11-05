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

static int	parse_rgb_part(char *tmp, int *i, int *j,
	t_map_data *data, int type)//////////////////////////////
{
	int		len;
	char	*substr;
	char	*part;
	int		value;

	if (tmp[*i] == ',')
		len = *i - *j;
	else
		len = *i - *j + 1;
	substr = ft_substr(tmp, *j, len);
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
	if (tmp[*i] == ',' && tmp[*i + 1] == '\0')
		return (1);
	*j = *i + 1;
	return (0);
}

static int	save_rgbs(char *line, t_map_data *data, int type)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	data->rgb_index = 0;
	tmp = ft_strdup(line);
	if (!tmp)
		return (1);
	while (tmp[++i])
	{
		if (tmp[i] == ',' || tmp[i + 1] == '\0')
		{
			if (parse_rgb_part(tmp, &i, &j, data, type))
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
			return (err_msg("Invalid Floor RGB value"), 1);
	}
	else if (first_line[0] == 'C')
	{
		data->ceiling_set = 1;
		if (save_rgbs(trimmed, data, CEILING))
			return (err_msg("Invalid Ceiling RGB value"), 1);
	}
	return (free(trimmed), 0);
}
