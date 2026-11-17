#include "includes/cub3d.h"

int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*dst;

	if (!tex || !tex->addr)
		return (COLOR_WHITE);
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = (char *)tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_window *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= win->win_width || y < 0 || y >= win->win_height)
		return ;
	dst = win->img_addr + (y * win->line_length
			+ x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
