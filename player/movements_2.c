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

void	set_player_speed(int keycode, t_window *mlx)
{
	if (keycode == KEY_1)
		mlx->player.move_speed = 0.01;
	else if (keycode == KEY_2)
		mlx->player.move_speed = 0.05;
	else if (keycode == KEY_3)
		mlx->player.move_speed = 0.10;
	else if (keycode == KEY_4)
		mlx->player.move_speed = 1.00;
}
