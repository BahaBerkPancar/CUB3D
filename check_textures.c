#include "cub3d.h"

int is_valid_direction(char *line)
{
	if(ft_strncmp(line, "NO", 2) == 0)
		return (1);
	if(ft_strncmp(line, "SO", 2) == 0)
		return (1);
	if(ft_strncmp(line, "WE", 2) == 0)
		return (1);
	if(ft_strncmp(line, "EA", 2) == 0)
		return (1);
	return (0);
}

int	is_valid_texture(char *line)
{
	char	*tmp;
	size_t	len;

	if(line[0] != ' ')
		return (ft_putstr_fd("Error: Invalid File Type\n", 2), 1);
	tmp = ft_strtrim(line, " \n\r\t");
	if (!tmp)
		return (ft_putstr_fd("Error: Invalid No File Name\n", 2), 1);
	len = ft_strlen(tmp);
	if (len > 0 && tmp[len - 1] == '\n')
		tmp[len - 1] = '\0';
	if (len < 4 || ft_strncmp(tmp + ft_strlen(tmp) - 4, ".xpm", 4) != 0)
		return (ft_putstr_fd("Error: Invalid File Type\n", 2), free(tmp), 1);
	if (access(tmp, F_OK) == -1)
		return (ft_putstr_fd("Error: Invalid File\n", 2), free(tmp), 1);
	return (free(tmp), 0);
}

void	save_textures(char *line, t_map_data *data, int type)
{
	if(type == NORTH)
		data->north_xpm = ft_strdup(line);
	else if(type == EASTH)
		data->easth_xpm = ft_strdup(line);
	else if(type == WEST)
		data->west_xpm = ft_strdup(line);
	else if(type == SOUTH)
		data->south_xpm = ft_strdup(line);
}

int	check_textures(char *line, t_map_data *data)
{
	char	*tmp;
	char	*save;
	char	*path;

	tmp = ft_strdup(line);
	if(!is_valid_direction(tmp))
		return (ft_putstr_fd("Error: Invalid Direction\n", 2), free(tmp), 1);
	else
		path = ft_strdup(tmp + 2);
	if(is_valid_texture(path))
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
		return (ft_putstr_fd("Error: Reaccuring Direction\n", 2), free(save), free(path), free(tmp), 1);
	return (free(save), free(path), free(tmp), 0);
}


// char *read_headers(char *line, int fd, t_map_data *data) 
// {
//     int textures = 0, colors = 0;
//     while (line) {
//         int i = 0;
//         while (line[i] && my_isspace(line[i])) i++;
//         if (!line[i]) { free(line); line = get_next_line(fd); continue; }

//         if (line[i] == '1' || line[i] == '0') return line; // map begins

//         if (!ft_strncmp(&line[i], "NO", 2) || !ft_strncmp(&line[i], "SO", 2) ||
//             !ft_strncmp(&line[i], "WE", 2) || !ft_strncmp(&line[i], "EA", 2)) {
//             if (check_textures(&line[i], data)) { free(line); return NULL; }
//             textures++;
//         } else if (line[i] == 'F' || line[i] == 'C') {
//             if (check_first_line(ft_strdup(&line[i]), data)) { free(line); return NULL; }
//             colors++;
//         } else {
//             ft_putstr_fd("Error: Unknown header\n", 2);
//             free(line); return NULL;
//         }

//         if (textures == 4 && colors == 2) {
//             free(line);
//             do { line = get_next_line(fd); } while (line && (!line[0] || my_isspace(line[0])));
//             return line;
//         }
//         free(line);
//         line = get_next_line(fd);
//     }
//     return NULL;
// }
