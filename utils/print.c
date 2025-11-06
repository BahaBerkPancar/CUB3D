#include "../includes/cub3d.h"

void	print_map(t_map_data *data)
{
	int	i;

	i = 0;
	if (!data->map)
		return ;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}

void	print_textures(t_map_data *data)
{
	printf("North Texture: %s\n", data->north_file);
	printf("South Texture: %s\n", data->south_file);
	printf("West Texture: %s\n", data->west_file);
	printf("East Texture: %s\n", data->easth_file);
}

void	print_rgbs(t_map_data *data)
{
	printf("Floor RGB: %d, %d, %d\n", data->floor[0],
		data->floor[1], data->floor[2]);
	printf("Ceiling RGB: %d, %d, %d\n", data->ceiling[0],
		data->ceiling[1], data->ceiling[2]);
}

void	err_msg(char *msg)
{
	if (!msg)
		return ;
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	print_everything(t_map_data *data)
{
	printf("////////////////////TEXTURES////////////////////////\n\n");
	print_textures(data);
	printf("\n////////////////////RGBS///////////////////////////\n\n");
	print_rgbs(data);
	printf("\n////////////////////MAP////////////////////////////\n\n");
	print_map(data);
	printf("\n///////////////////////////////////////////////////\n");
}
