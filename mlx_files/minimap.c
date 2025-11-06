#include "../includes/cub3d.h"

void	draw_tile(t_window *mlx, int x, int y, int color)
{
	int	i;
	int	j;
	int	border;
	int	size;

	border = 1;
	size = mlx->tile_size;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			if (i < border || j < border
				|| i >= size - border || j >= size - border)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr,
					x + i, y + j, COLOR_BORDER);
			else
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr,
					x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	set_color(char c, int *color)
{
	if (c == '1')
		*color = COLOR_WALL;
	else if (c == '0')
		*color = COLOR_FLOOR;
	else if (c == ' ')
		*color = COLOR_SPACE;
	else
		*color = COLOR_FLOOR;
}

void	print_minimap(t_window *mlx)
{
	int		x;
	int		y;
	int		color;
	int		offset[2];

	offset[0] = 5;
	offset[1] = 5;
	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			set_color(mlx->map[y][x], &color);
			draw_tile(mlx, offset[0] + x * mlx->tile_size,
				offset[1] + y * mlx->tile_size, color);
			x++;
		}
		y++;
	}
}
