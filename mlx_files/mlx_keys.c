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
	if (keycode == KEY_ESC)
		handle_close(mlx);
	if (keycode == KEY_W || keycode == KEY_UP)
		mlx->move_forward = 1;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		mlx->move_backward = 1;
	if (keycode == KEY_A)
		mlx->move_left = 1;
	if (keycode == KEY_D)
		mlx->move_right = 1;
	if (keycode == KEY_LEFT)
		mlx->rotate_left = 1;
	if (keycode == KEY_RIGHT)
		mlx->rotate_right = 1;
	if (keycode == KEY_TAB)
		mlx->show_minimap = 1;
	if (keycode == KEY_P)
		reset_player(mlx);
	if (keycode >= KEY_1 && keycode <= KEY_4)
		set_player_speed(keycode, mlx);
	return (0);
}

// codes might need to change in linux
int	handle_keyrelease(int keycode, t_window *mlx)
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
