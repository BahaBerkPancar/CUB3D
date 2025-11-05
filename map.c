#include "cub3d.h"

int		check_textures(char *line, t_map_data *data);
char	*read_rgbs(char *first_line, int fd, t_map_data *data);

char	*read_textures(int fd, t_map_data *data)
{
	char	*line;
	int		i;

	i = 0; 
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] && my_isspace(line[i]))
			i++;
		if (!line[i])
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (line[i] == 'F' || line[i] == 'C' || line[i] == '1' || line[i] == '0')
			return(line);
		if (check_textures(&line[i], data) == 1)
			return (free(line), NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), ft_strdup(""));///////change
}

int	read_map(char *map_file, t_map_data *data)
{
	int		fd;
	char	*line;
	char	*tmp;
	
	line = NULL;
	fd = open(map_file, O_RDONLY);
	line = read_textures(fd, data);
	if (!data->easth_xpm || !data->west_xpm || !data->south_xpm || !data->north_xpm)
		return (ft_putstr_fd("Error: Missing Texture\n", 2), free(line), 1);
	if (line == NULL)
		return (free(line), close(fd), 1);
	tmp = read_rgbs(ft_strtrim(line, " \n\r\t"), fd, data);
	if (tmp == NULL)
		return (free(line), close(fd), 1);
	printf("%d,%d,%d\n", data->floor[0], data->floor[1], data->floor[2]);
	printf("%d,%d,%d\n", data->ceiling[0], data->ceiling[1], data->ceiling[2]);
	printf("%s\n", data->easth_xpm);
	printf("%s\n", data->north_xpm);
	printf("%s\n", data->west_xpm);
	printf("%s\n", data->south_xpm);
	close(fd);
	free(line);
	return (0);
}

