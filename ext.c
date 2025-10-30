#include "cub3d.h"

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	if (!str)
		return;
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

int my_isspace(char c)
{
    return (c == ' '  ||
           c == '\t' ||
           c == '\n' ||
           c == '\r' ||
           c == '\v' ||
           c == '\f');
}
