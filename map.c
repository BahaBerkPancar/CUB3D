#include "cub3d.h"

int	check_textures(char *line, t_map_data *data);

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
	if (!data->easth_xpm || !data->west_xpm || !data->south_xpm || !data->north_xpm)
		return (ft_putstr_fd("Error: Missing Texture\n", 2), free(line), NULL);
	printf("done with reading textures\n");
	return (free(line), ft_strdup(""));///////change 
}

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

void	save_rgbs(char *line, t_map_data *data, int type)
{
	////improve and get type checking from readrgbs 
	/// check if rgbs have any more checks
	if (type == FLOOR)
		data->floor = ft_strdup(line);
	else if (type == CEILING)
		data->ceiling = ft_strdup(line);
}

char	*read_rgbs(char *first_line, int fd, t_map_data *data)
{
	char	*trimmed;
	int		i;

	i = 0;
	trimmed = ft_strtrim(first_line + 1, " \n\r\t");
	if (first_line[0] == 'F')
		save_rgbs(trimmed, data, FLOOR);
	else if (first_line[0] == 'C')
		save_rgbs(trimmed, data, CEILING);
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
			return(free(trimmed), first_line);
		if (first_line[0] == 'F')
			save_rgbs(trimmed, data, FLOOR);
		else if (first_line[0] == 'C')
			save_rgbs(trimmed, data, CEILING);
		free(first_line);
		first_line = get_next_line(fd);
	}
	free(trimmed);
	return (free(first_line), ft_strdup(""));
}
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

int	read_map(char *map_file, t_map_data *data)
{
	int		fd;
	char	*line;
	
	line = NULL;
	fd = open(map_file, O_RDONLY);
	line = read_textures(fd, data);
	if (line == NULL)
		return (free(line), close(fd), 1);
	read_rgbs(ft_strtrim(line, " \n\r\t"), fd, data);
	printf("%s\n", data->floor);
	// printf("%s\n", data->ceiling);
	close(fd);
	free(line);
	return (0);
}

