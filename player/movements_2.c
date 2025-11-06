#include "../includes/cub3d.h"

void	rotate_left(t_window *mlx)
{
	double	old_dir_x;
	double	theta;

	theta = mlx->player.rot_speed;
	old_dir_x = mlx->player.dir_x;
	mlx->player.dir_x = mlx->player.dir_x * cos(theta)
		- mlx->player.dir_y * sin(theta);
	mlx->player.dir_y = old_dir_x * sin(theta)
		+ mlx->player.dir_y * cos(theta);
}

void	rotate_right(t_window *mlx)
{
	double	old_dir_x;
	double	theta;

	theta = -mlx->player.rot_speed;
	old_dir_x = mlx->player.dir_x;
	mlx->player.dir_x = mlx->player.dir_x * cos(theta)
		- mlx->player.dir_y * sin(theta);
	mlx->player.dir_y = old_dir_x * sin(theta)
		+ mlx->player.dir_y * cos(theta);
}
