#include "../includes/cub3d.h"

int	handle_close(t_window *mlx)
{
	clean_mlx(mlx);
	printf("Exited...\n");
	exit(0);
	return (0);
}

int	update_game(t_window *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->move_forward)
		move_forward(mlx);
	if (mlx->move_backward)
		move_backward(mlx);
	if (mlx->move_left)
		move_left(mlx);
	if (mlx->move_right)
		move_right(mlx);
	if (mlx->rotate_left)
		rotate_left(mlx);
	if (mlx->rotate_right)
		rotate_right(mlx);
	if (mlx->show_minimap)
	{
		print_minimap(mlx);
		print_player(mlx);
	}
	return (0);
}

int	handle_keypress(int keycode, t_window *mlx)
{
	if (keycode == 53)
		handle_close(mlx);
	if (keycode == 13 || keycode == 126)
		mlx->move_forward = 1;
	if (keycode == 1 || keycode == 125)
		mlx->move_backward = 1;
	if (keycode == 0)
		mlx->move_left = 1;
	if (keycode == 2)
		mlx->move_right = 1;
	if (keycode == 123)
		mlx->rotate_left = 1;
	if (keycode == 124)
		mlx->rotate_right = 1;
	if (keycode == 48)
		mlx->show_minimap = 1;
	if (keycode == 35)
		reset_player(mlx);
	return (0);
}

int	handle_keyrelease(int keycode, t_window *mlx) // codes might need to change in linux
{
	if (keycode == 13 || keycode == 126)
		mlx->move_forward = 0;
	if (keycode == 1 || keycode == 125)
		mlx->move_backward = 0;
	if (keycode == 0)
		mlx->move_left = 0;
	if (keycode == 2)
		mlx->move_right = 0;
	if (keycode == 123)
		mlx->rotate_left = 0;
	if (keycode == 124)
		mlx->rotate_right = 0;
	if (keycode == 48)
		mlx->show_minimap = 0;
	return (0);
}
