#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "sys/time.h"
#include "../get_next_line/get_next_line.h"
#include "structs.h"

int		check_map(int ac, char **av);
void	ft_strrev(char *str);
int		read_map(char *map_file, t_map_data *data);
int		my_isspace(char c);
int		str_isdigit(const char *str);

#endif