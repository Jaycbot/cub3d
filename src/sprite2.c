/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:31:14 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:31:15 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
/*
* normalize because atan2 can represent the value between PI and -PI
*/
void	calc_sp(t_config *c)
{
	int	index;
	t_sprite *s;

	index = 0;
	while (index < g_sprite_count)
	{
		s = &c->sprites[index];
		s->dir = atan2(s->pos.y - c->camera.y ,
			s->pos.x - c->camera.x);
		while (s->dir - c->camera.rotation_angle > M_PI)
			s->dir -= 2 * M_PI;
		while (s->dir - c->camera.rotation_angle < - M_PI)
			s->dir += 2 * M_PI;
		s->cam_dist = hypot(c->camera.x - s->pos.x,
			c->camera.y - s->pos.y);
		s->size = c->width / s->cam_dist * c->tile;
		s->offset_x = (s->dir - c->camera.rotation_angle) * c->width / c->fov
		+ (c->width / 2) - (s->size / 2);
		s->offset_y = (c->height / 2) - (s->size / 2);
		++index;
	}
}

void	sort_sp(t_config *c)
{
	int		i;
	int		j;
	t_sprite	temp;

	i = 0;
	while (i < g_sprite_count)
	{
		j = i;
		while (j < g_sprite_count - 1)
		{
			if (c->sprites[j].cam_dist < c->sprites[j + 1].cam_dist)
			{
				temp = c->sprites[j];
				c->sprites[j] = c->sprites[j + 1];
				c->sprites[j + 1] = temp;
			}
			++j;
		}
		++i;
	}
}

static	void	pick_color(t_config *c, t_sprite *sp, int x, int y)
{
	int	color;
	int	relative_x;
	int	relative_y;
	color = 0;

	relative_x = x * c->textures[4].img.img_h / sp->size;
	relative_y = y * c->textures[4].img.img_w / sp->size;
	color = pick_pixel(&c->textures[4].img, relative_x, 
	relative_y);
	if (color)
		insert_pixel(&c->img, sp->offset_x + x, sp->offset_y
			+ y, color);
}

int		is_sprite(double x, double y, t_config *c)
{
	int deltax;
	int deltay;

	if (x < 0 || x > c->width || y < 0 || y > c->height)
		return (0);
	deltax = (int)floor(x / c->tile);
	deltay = (int)floor(y / c->tile);
	if (deltax <= 0 || deltax >= c->cols
			|| deltay <= 0 || deltay >= c->rows)
		return (0);
	if (c->map[deltay][deltax] == '2')
		return (1);
	return (0);
}

void	transform_sprite(t_config *c, int i)
{
	int			x;
	int			y;
	t_sprite	*s;

	y = 0;
	s = &c->sprites[i];
	while (y < s->size)
	{
		if (s->offset_y + y >= 0 && s->offset_y + y < c->height)
		{
			x = 0;
			while (x < s->size)
			{
				if (s->offset_x + x >=  0 && s->offset_x + x < c->width
					&& c->rays[s->offset_x + x].actual_dist > s->cam_dist)
					pick_color(c, s, x, y);
				++x;
			}
		}
		++y;
	}
}
