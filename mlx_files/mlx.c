#include "../includes/cub3d.h"

// this will completely change it is just to test
int	put_image_to_window(t_window *mlx)
{
	void	*images[4];
	int		x;
	int		y;
	int		i;

	images[0] = mlx->north_xpm;
	images[1] = mlx->south_xpm;
	images[2] = mlx->easth_xpm;
	images[3] = mlx->west_xpm;
	x = 0;
	y = 0;
	i = 0;
	while (i < 4)
	{
		if (images[i])
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, images[i], x, y);
			x += mlx->img_width;
			if (x + mlx->img_width > mlx->win_width)
			{
				x = 0;
				y += mlx->img_height;
			}
		}
		i++;
	}
	return (0);
}

void	start_window(t_window *mlx)
{
	put_image_to_window(mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, handle_keypress, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, handle_keyrelease, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, handle_close, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update_game, mlx);
	mlx_loop(mlx->mlx_ptr);
}
