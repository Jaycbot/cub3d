/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:21:24 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:21:25 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_window(t_config *c)
{
	if (c->width < 500 || c->height < 500)
		error_etc("ERROR\nMinimum window size is 500 x 500", c);
	c->win.win = mlx_new_window(c->mlx, c->width, c->height, "cub3d");
	c->img.img = mlx_new_image(c->mlx, c->width, c->height);
	c->img.data = mlx_get_data_addr(c->img.img, &c->img.bpp,
		&c->img.size_l, &c->img.endian);
}

void	init_config(t_config *config)
{
	int	i;

	i = 0;
	config->width = 0;
	config->height = 0;
	config->rows = 0;
	config->cols = 0;
	config->tile = 0;
	config->map = NULL;
	config->color_c = 0;
	config->color_f = 0;
	config->fov = 50 * M_PI / 180;
	config->camera.x = 0;
	config->camera.y = 0;
	config->camera.rotation_angle = M_PI;
	config->camera.turndirection = 0;
	config->camera.walkdirection = 0;
	config->camera.walkd_right_left = 0;
	config->camera.turnspeed = .11;
	config->camera.walkspeed = 5;
	config->rays = NULL;
	config->sprites = NULL;
	while (i < 5)
		config->textures[i++].path = NULL;
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *str;

	str = s;
	while (n--)
		*str++ = c;
	return (s);
}