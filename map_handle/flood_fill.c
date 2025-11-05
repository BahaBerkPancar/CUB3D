#include "../includes/cub3d.h"

void	flood_fill(char **map, int y, int x, int **visited)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return ;
	if (map[y][x] == ' ' || visited[y][x])
		return ;
	visited[y][x] = 1;
	flood_fill(map, y + 1, x, visited);
	flood_fill(map, y - 1, x, visited);
	flood_fill(map, y, x + 1, visited);
	flood_fill(map, y, x - 1, visited);
}
