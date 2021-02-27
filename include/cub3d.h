/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:06:25 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 13:20:37 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

# define ESC 					53
# define W 						13
# define A 						0
# define S 						1
# define D 						2
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define FALSE					0
# define TRUE					1
# define FORWARD				1
# define BACKWARD				-1
# define LEFT					1
# define RIGHT					-1

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define BUFFER_SIZE 			32
# define MAP_COMPONENTS			"012EWSN "

# define ID_RESOLUTION			6
# define ID_NORTH				0
# define ID_SOUTH				1
# define ID_WEST				2
# define ID_EAST				3
# define ID_SPRITE				4
# define ID_FLOOR				5
# define ID_CEILING				7
# define ID_MAP					8
# define WALL					1

int				g_camera_count;
int				g_sprite_count;

typedef struct	s_win
{
	void	*win;
	int		win_h;
	int		win_w;
}				t_win;

typedef struct	s_img
{
	void			*img;
	char			*data;
	int				bpp;
	int				size_l;
	int				endian;
	int				img_w;
	int				img_h;
}				t_img;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_camera
{
	double	x;
	double	y;
	double	rotation_angle;
	int		turndirection;
	int		walkdirection;
	int		walkd_right_left;
	double	turnspeed;
	double	walkspeed;
}				t_camera;

typedef struct	s_texture
{
	char	*path;
	t_img	img;
}				t_texture;

typedef struct	s_sprite
{
	double	dir;
	double	cam_dist;
	int		size;
	int		offset_x;
	int		offset_y;
	t_pos	pos;
}				t_sprite;

typedef struct	s_ray
{
	t_pos		hit_p;
	double		bottom_strip;
	double		top_strip;
	double		angle;
	double		actual_dist;
	int			washitvertical;
	int			isfacingup;
	int			isfacingdown;
	int			isfacingleft;
	int			isfacingright;
	int			direction;
}				t_ray;

typedef struct	s_bmp
{
	unsigned char	header[54];
	int				*body;
}				t_bmp;

typedef struct	s_config
{
	void		*mlx;
	t_win		win;
	t_img		img;
	t_camera	camera;
	t_sprite	*sprites;
	t_ray		*rays;
	t_bmp		bmp;
	int			rows;
	int			cols;
	double		tile;
	int			width;
	int			height;
	double		fov;
	t_texture	textures[5];
	int			color_f;
	int			color_c;
	int			check_size[8];
	double		rotation_speed;
	double		dist_to_plane;
	char		**map;

}				t_config;

void			init_sprite(t_sprite *s);
void			init_config(t_config *config);
void			compensate_p(t_pos *p, double width, double height);
int				key_release(int keycode, t_config *config);
int				key_press(int keycode, t_config *config);
int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *str);
char			*ft_strdup(char *str);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *str, unsigned int start, size_t len);
int				is_equal(char *a, char *b);
int				is_in(char *s, int c);
int				is_space(char c);
int				empty_line_check(char *line);
int				extenstion_check(char *filename);
int				contents_check(char *line);
int				is_capital(char c);
void			error_etc(char *msg);
int				identifier_check(char *line);
void			check_double_position(char c);
int				free_line(char *line);
char			*bridge(char **backup, char *to_add);
char			**ft_split(char const *s, char c);
int				parse_resolution(t_config *c, char *line);
int				is_digit(char c);
int				ft_atoi(const char *nptr);
char			*parse_path(char *line);
int				parse_color(char *line);
double			max(double a, double b);
int				trimmed_size(char *a);
void			free_all(t_config *c);
int				check_and_find(t_config *c);
double			normalize(double angle);
void			move_camera(t_config *c);
void			parse_texture(t_config *c);
int				to_coord(int x, int y, t_texture t);
void			error_with_message(char *prefix);
void			print_floor(t_config *c, t_ray *ray, int col);
void			print_ceiling(t_config *c, t_ray *ray, int col);
void			set_p(t_pos *pos, double x, double y);
int				blocked(t_config *c, double x, double y);
int				is_sprite(double x, double y, t_config *c);
t_pos			wall_hit_v(t_config *c, t_ray *ray, double angle);
t_pos			wall_hit_h(t_config *c, t_ray *ray, double angle);
double			transform_to_texture(t_config *c, t_ray *ray, int stripid);
int				parse_file(t_config *c, char *filepath);
void			raycast(t_config *c, t_ray *rays);
void			init_window(t_config *c);
void			find_direction(t_ray *ray);
void			set_sprite(t_config *c);
void			sort_sp(t_config *c);
void			calc_sp(t_config *c);
void			transform_sprite(t_config *c, int i);
void			render_sprites(t_config *c);
void			insert_pixel(t_img *img, int x, int y, int color);
void			*ft_memset(void *s, int c, size_t n);
int				pick_pixel(t_img *img, int x, int y);
void			check_resolution(t_config *c);

#endif
