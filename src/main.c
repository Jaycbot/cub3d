/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:22:06 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 12:27:29 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void			check_resolution(t_config *c)
{
	int max_width;
	int max_height;

	mlx_get_screen_size(c->mlx, &max_width, &max_height);
	if (c->width > max_width)
		c->width = max_width;
	if (c->height > max_height)
		c->height = max_height;
}


int				close_win(void *param)
{
	t_config	*c;

	c = (t_config *)param;
	free_all(c);
	exit(0);
}

int				main_loop(t_config *config)
{
	move_camera(config);
	raycast(config, config->rays);
	render_sprites(config);
	mlx_put_image_to_window(config->mlx, config->win.win,
		config->img.img, 0, 0);
	mlx_do_sync(config->mlx);
	return (0);
}
static	void	set_rays(t_config *c)
{
	t_ray	*rays;

	if (!(rays = (t_ray *)malloc(sizeof(t_ray) * c->width)))
		error_etc("ERROR\nMalloc failed", c);
	c->rays = rays;
}
static	void	set_config(t_config *c, char *path)
{
	init_config(c);
	g_camera_count = 0;
	c->bmp.body = NULL;
	if (!parse_file(c, path))
		error_etc("ERROR\nFalid to load file", c);
	if (!check_and_find(c))
		error_etc("ERROR\nInvalidMap", c);
	c->bmp.body = (int *)malloc(sizeof(int) * c->width * c->height);
	if (!c->bmp.body)
		error_etc("ERROR\nMalloc faild", c);
	parse_texture(c);
	init_window(c);
	set_rays(c);
	set_sprite(c);
}

int				main(int argc, char **argv)
{
	t_config	config;

	config = (t_config) {0};
	if (!(argc == 2 || (argc == 3 && is_equal(argv[2], "--save"))))
		error_etc("ERROR\nInvalid Arguments", &config);
	config.mlx = mlx_init();
	if (!config.mlx)
		error_etc("ERROR\nFalid to load mlx", &config);
	set_config(&config, argv[1]);
	if (argc == 3 && is_equal(argv[2], "--save"))
		save_bmp_format(&config);
	mlx_hook(config.win.win, X_EVENT_KEY_PRESS, 0, key_press, &config);
	mlx_hook(config.win.win, X_EVENT_KEY_RELEASE, 0, key_release, &config);
	mlx_hook(config.win.win, X_EVENT_KEY_EXIT, 0, close_win, &config);
	mlx_loop_hook(config.mlx, main_loop, &config);
	mlx_loop(config.mlx);
	return (0);
}
