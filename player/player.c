#include "../includes/cub3d.h"

void	reset_player(t_window *mlx)
{
	mlx->player.x = mlx->player_start_x;
	mlx->player.y = mlx->player_start_y;
	mlx->player.dir_x = mlx->player_start_dir_x;
	mlx->player.dir_y = mlx->player_start_dir_y;
	mlx->player.move_speed = 0.05;
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->show_minimap)
	{
		print_minimap(mlx);
		print_player(mlx);
	}
}

void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

void	print_player(t_window *mlx)
{
	int	player_x;
	int	player_y;
	int	player_size;
	int	color;

	player_x = 5 + (int)(mlx->player.x * mlx->tile_size);
	player_y = 5 + (int)(mlx->player.y * mlx->tile_size);
	player_size = mlx->tile_size / 2;
	color = COLOR_PLAYER;
	draw_tile(mlx, player_x - player_size / 2,
		player_y - player_size / 2, color);
}

void	set_player_ints(t_window *mlx, int x, int y, char c)
{
	mlx->player.x = x + 0.5;
	mlx->player.y = y + 0.5;
	mlx->player.move_speed = 0.2;
	mlx->player.rot_speed = 0.05;
	set_player_direction(&mlx->player, c);
	mlx->player_start_x = mlx->player.x;
	mlx->player_start_y = mlx->player.y;
	mlx->player_start_dir_x = mlx->player.dir_x;
	mlx->player_start_dir_y = mlx->player.dir_y;
}

void	init_player(t_window *mlx)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			c = mlx->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_player_ints(mlx, x, y, c);
				mlx->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
