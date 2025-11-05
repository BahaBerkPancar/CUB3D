#include "../includes/cub3d.h"

int	is_valid_direction(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (1);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (1);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (1);
	return (0);
}

int	is_valid_texture(char *line)
{
	char	*tmp;
	size_t	len;

	if (line[0] != ' ' && line[0] != '	')
		return (err_msg("Invalid File Type"), 1);
	tmp = ft_strtrim(line, " \n\r\t");
	if (!tmp)
		return (err_msg("Invalid No File Name"), 1);
	len = ft_strlen(tmp);
	if (len > 0 && tmp[len - 1] == '\n')
		tmp[len - 1] = '\0';
	if (len < 4 || ft_strncmp(tmp + ft_strlen(tmp) - 4, ".xpm", 4) != 0)
		return (err_msg("Invalid File Type"), free(tmp), 1);
	if (access(tmp, F_OK) == -1)
		return (err_msg("Invalid File"), free(tmp), 1);
	return (free(tmp), 0);
}

void	save_textures(char *line, t_map_data *data, int type)
{
	if (type == NORTH)
		data->north_xpm = ft_strdup(line);
	else if (type == EASTH)
		data->easth_xpm = ft_strdup(line);
	else if (type == WEST)
		data->west_xpm = ft_strdup(line);
	else if (type == SOUTH)
		data->south_xpm = ft_strdup(line);
}

int	check_textures(char *line, t_map_data *data)
{
	char	*tmp;
	char	*save;
	char	*path;

	tmp = ft_strdup(line);
	if (!is_valid_direction(tmp))
		return (err_msg("Invalid Direction"), free(tmp), 1);
	else
		path = ft_strdup(tmp + 2);
	if (is_valid_texture(path))
		return (free(path), free(tmp), 1);
	free(tmp);
	tmp = ft_strtrim(path, " \n\r\t");
	save = ft_strtrim(line, " \n\r\t");
	if (save[0] == 'N' && !data->north_xpm)
		save_textures(tmp, data, NORTH);
	else if (save[0] == 'W' && !data->west_xpm)
		save_textures(tmp, data, WEST);
	else if (save[0] == 'E' && !data->easth_xpm)
		save_textures(tmp, data, EASTH);
	else if (save[0] == 'S' && !data->south_xpm)
		save_textures(tmp, data, SOUTH);
	else
		return (free_4(save, path, tmp, NULL), 1);
	return (free_4(save, path, tmp, NULL), 0);
}
