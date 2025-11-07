#include "../includes/cub3d.h"

void	start_window(t_window *mlx)
{
	mlx_hook(mlx->win_ptr, 2, 1L << 0, handle_keypress, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, handle_keyrelease, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, handle_close, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update_game, mlx);
	mlx_loop(mlx->mlx_ptr);
}
