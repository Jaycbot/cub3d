/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:19:29 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:21:12 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		insert_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int			pick_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->data + (y * img->size_l + x * (img->bpp / 8));
	return (*(unsigned int*)dst);
}

void	print_floor(t_config *c, t_ray *ray, int col)
{
		int	row;

		row = ray->bottom_strip;
		while (row < c->height)
		{
			insert_pixel(&c->img, col, row, c->color_f);
			++row;
		}
}

void	print_ceiling(t_config *c, t_ray *ray, int col)
{
		int	row;

		row = 0;
		while (row < ray->top_strip)
		{
			insert_pixel(&c->img, col, row, c->color_c);
			++row;
		}
}

static	void	texture_img(t_config *c, int index)
{
	int			x;
	int			y;
	t_texture	*t;

	t = &c->textures[index];
	t->img.img = mlx_xpm_file_to_image(c->mlx, 
	t->path, &t->img.img_w, &t->img.img_h);
	if (!t->img.img)
		error_etc("ERROR\nInvalid Texture path", c);
	t->img.data = mlx_get_data_addr(t->img.img, &t->img.bpp,
		&t->img.size_l, &t->img.endian);
}

void		parse_texture(t_config *c)
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		texture_img(c, i);
		free(c->textures[i].path);
		c->textures[i].path = NULL;
		++i;
	}
	i = 0;
	j = 0;
	while (j < 8)
	{
		c->check_size[j] = c->textures[i].img.img_w;
		++j;
		c->check_size[j] = c->textures[i].img.img_h;
		++j;
		++i;
	}
}
