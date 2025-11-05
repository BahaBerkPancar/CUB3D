#include "../includes/cub3d.h"

int	str_isdigit(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i++;
	j = 0;
	i--;
	while (j < i)
	{
		tmp = str[j];
		str[j] = str[i];
		str[i] = tmp;
		j++;
		i--;
	}
}

int	my_isspace(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\r'
		|| c == '\v'
		|| c == '\n'
		|| c == '\f');
}

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && (!line[0]))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

size_t	get_max_width(char **map)
{
	size_t	max;
	size_t	len;
	int		i;

	i = 0;
	max = 0;
	while (map && map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}
