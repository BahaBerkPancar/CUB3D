#include "../includes/cub3d.h"

int	handle_close(t_window *mlx)
{
	clean_mlx(mlx);
	printf("Exited...\n");
	exit(0);
	return (0);
}

int	update_game(t_window *mlx)//this is temprory it will ben changed after 3d image 
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->move_forward)
		printf("Moving forward\n");
	if (mlx->move_down)
		printf("Moving backward\n");
	if (mlx->move_left)
		printf("Moving left\n");
	if (mlx->move_right)
		printf("Moving right\n");
	if (mlx->rotate_left)
		printf("Rotating left\n");
	if (mlx->rotate_right)
		printf("Rotating right\n");
	if (mlx->show_minimap)
		print_minimap(mlx);//minimap
	return (0);
}

int	handle_keypress(int keycode, t_window *mlx) // codes might need to change in linux
{
	if (keycode == 53) // ESC
		handle_close(mlx);
	if (keycode == 13 || keycode == 126) // W or ↑
		mlx->move_forward = 1;
	if (keycode == 1 || keycode == 125) // S or ↓
		mlx->move_down = 1;
	if (keycode == 0) // A
		mlx->move_left = 1;
	if (keycode == 2) // D
		mlx->move_right = 1;
	if (keycode == 123) // ←
		mlx->rotate_left = 1;
	if (keycode == 124) // →
		mlx->rotate_right = 1;
	if (keycode == 48) // TAB
		mlx->show_minimap = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_window *mlx) // codes might need to change in linux
{
	if (keycode == 13 || keycode == 126) // W or ↑ 
		mlx->move_forward = 0;
	if (keycode == 1 || keycode == 125) // S or ↓
		mlx->move_down = 0;
	if (keycode == 0) // A
		mlx->move_left = 0;
	if (keycode == 2) // D
		mlx->move_right = 0;
	if (keycode == 123) // ←
		mlx->rotate_left = 0;
	if (keycode == 124) // →
		mlx->rotate_right = 0;
	if (keycode == 48) // TAB
		mlx->show_minimap = 0;
	return (0);
}
