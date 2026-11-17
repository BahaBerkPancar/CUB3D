#ifndef CUB3D_H
# define CUB3D_H

# define COLOR_WALL		0xFF0000
# define COLOR_WHITE	0xFF0000
# define COLOR_FLOOR	0x000000
# define COLOR_SPACE	0x111111
# define COLOR_PLAYER	0xFFFFFF
# define COLOR_BORDER	0x333333

# define KEY_ESC        53
# define KEY_W          13
# define KEY_UP         126
# define KEY_S          1
# define KEY_DOWN       125
# define KEY_A          0
# define KEY_D          2
# define KEY_LEFT       123
# define KEY_RIGHT      124
# define KEY_TAB        48
# define KEY_P          35
# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "sys/time.h"
# include "../get_next_line/get_next_line.h"
# include "structs.h"
# include "../minilibx_opengl_20191021/mlx.h"

void		print_map(t_map_data *data);
void		print_textures(t_map_data *data);
void		print_rgbs(t_map_data *data);
void		print_everything(t_map_data *data);
void		err_msg(char *msg);

void		free_data(t_map_data *data);
void		clean_mlx(t_window *mlx);
void		free_pointer(void **lines);
void		free_4(char *a, char *b, char *c, char *d);

void		ft_strrev(char *str);
int			my_isspace(char c);
int			str_isdigit(const char *str);
char		*skip_empty_lines(int fd);
int			is_valid_direction(char *line);
size_t		get_max_width(char **map);
int			**change_to_int(char **map);

int			check_disconnected_map(t_map_data *data, int player_y,
				int player_x);
int			check_invalid_chars(t_map_data *data);
int			check_open_map(t_map_data *data);
int			check_player(t_map_data *data);
int			check_headers(t_map_data *data);
int			check_args(int ac, char **av);
int			check_textures(char *line, t_map_data *data);
int			check_first_line(char *first_line, t_map_data *data);

int			map_checks(t_map_data *data);
int			normalize_map(t_map_data *data);
void		flood_fill(char **map, int y, int x, int **visited);
int			read_map(char *map_file, t_map_data *data);
char		*read_headers(char *line, int fd, t_map_data *data);
char		**copy_map(t_map_data *data, t_window *mlx);

t_window	*init_mlx(t_map_data *data);
void		start_window(t_window *mlx);
int			create_xpm_image(t_window *mlx, t_map_data *data);
int			load_texture(t_window *mlx, t_texture *tex, char *file, char *msg);
int			create_frame(t_window *mlx);
void		draw_tile(t_window *mlx, int x, int y, int color);

int			handle_keyrelease(int keycode, t_window *mlx);
int			handle_keypress(int keycode, t_window *mlx);
int			handle_close(t_window *mlx);
int			update_game(t_window *mlx);
void		print_minimap(t_window *mlx);

double		perform_dda(t_window *win, double ray_dir_x, double ray_dir_y,
				int *side, double *hit_x);
void		render_frame(t_window *win);
int			rgb_to_int(int rgb[3]);
int			get_texture_pixel(t_texture *tex, int x, int y);
void		put_pixel(t_window *win, int x, int y, int color);

void		print_player(t_window *mlx);
void		init_player(t_window *mlx);
void		reset_player(t_window *mlx);
void		set_player_speed(int keycode, t_window *mlx);

void		move_backward(t_window *mlx);
void		move_forward(t_window *mlx);
void		move_right(t_window *mlx);
void		move_left(t_window *mlx);
void		rotate_right(t_window *mlx);
void		rotate_left(t_window *mlx);

#endif