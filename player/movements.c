#include "../includes/cub3d.h"

static int	is_wall(t_window *mlx, double x, double y)
{
	int	map_x;
	int	map_y;
	int	line_len;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= mlx->map_height)
		return (1);
	if (!mlx->map[map_y])
		return (1);
	line_len = ft_strlen(mlx->map[map_y]);
	if (map_x < 0 || map_x >= line_len)
		return (1);
	if (mlx->map[map_y][map_x] == '1' || mlx->map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

void	move_forward(t_window *mlx)
{
	double	next_x;
	double	next_y;
	double	pad;

	pad = 0.4;
	next_x = mlx->player.x + mlx->player.dir_x * mlx->player.move_speed;
	next_y = mlx->player.y + mlx->player.dir_y * mlx->player.move_speed;
	if (!is_wall(mlx, next_x + mlx->player.dir_x * pad, mlx->player.y))
		mlx->player.x = next_x;
	if (!is_wall(mlx, mlx->player.x, next_y + mlx->player.dir_y * pad))
		mlx->player.y = next_y;
}

void	move_backward(t_window *mlx)
{
	double	next_x;
	double	next_y;
	double	pad;

	pad = 0.4;
	next_x = mlx->player.x - mlx->player.dir_x * mlx->player.move_speed;
	next_y = mlx->player.y - mlx->player.dir_y * mlx->player.move_speed;
	if (!is_wall(mlx, next_x - mlx->player.dir_x * pad, mlx->player.y))
		mlx->player.x = next_x;
	if (!is_wall(mlx, mlx->player.x, next_y - mlx->player.dir_y * pad))
		mlx->player.y = next_y;
}

void	move_left(t_window *mlx)
{
	double	next_x;
	double	next_y;
	double	pad;

	pad = 0.4;
	next_x = mlx->player.x + mlx->player.dir_y * mlx->player.move_speed;
	next_y = mlx->player.y - mlx->player.dir_x * mlx->player.move_speed;
	if (!is_wall(mlx, next_x + mlx->player.dir_y * pad, mlx->player.y))
		mlx->player.x = next_x;
	if (!is_wall(mlx, mlx->player.x, next_y - mlx->player.dir_x * pad))
		mlx->player.y = next_y;
}

void	move_right(t_window *mlx)
{
	double	next_x;
	double	next_y;
	double	pad;

	pad = 0.4;
	next_x = mlx->player.x - mlx->player.dir_y * mlx->player.move_speed;
	next_y = mlx->player.y + mlx->player.dir_x * mlx->player.move_speed;
	if (!is_wall(mlx, next_x - mlx->player.dir_y * pad, mlx->player.y))
		mlx->player.x = next_x;
	if (!is_wall(mlx, mlx->player.x, next_y + mlx->player.dir_x * pad))
		mlx->player.y = next_y;
}
