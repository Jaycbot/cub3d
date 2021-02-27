/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:39:18 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:39:19 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	info_sprites(t_config *c)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	index = 0;
	while (c->map[y])
	{
		x = 0;
		while (c->map[y][x])
		{
			if (c->map[y][x] == '2')
			{
				c->sprites[index].pos.x = (x + .5) * c->tile;
				c->sprites[index].pos.y = (y + .5) * c->tile;
				++index;
			}
			++x;
		}
		++y;
	}
}

void		set_sprite(t_config *c)
{
	if (g_sprite_count == 0)
		return ;
	c->sprites = (t_sprite *)malloc(sizeof(t_sprite) * g_sprite_count);
	if (!c->sprites)
		error_etc("ERROR\nMalloc Failed", c);
	info_sprites(c);
}

void	render_sprites(t_config *c)
{
	int	i;

	i = 0;
	calc_sp(c);
	sort_sp(c);
	while (i < g_sprite_count)
	{
		transform_sprite(c, i);
		++i;
	}
}