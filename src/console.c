/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:09:10 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 13:17:27 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		blocked(t_config *c, double x, double y)
{
	int	modx;
	int	mody;

	if (x < 0 || x > c->cols * c->tile || y < 0 || y > c->height)
		return (1);
	modx = (int)floor(x / c->tile);
	mody = (int)floor(y / c->tile);
	if (modx < 0 || modx >= c->cols || mody < 0 || mody >= c->rows)
		return (1);
	if (c->map[mody][modx] == '1' || c->map[mody][modx] == '2')
	{
		if (c->map[mody][modx] == '1')
			return (1);
		if (c->map[mody][modx] == '2')
			return (2);
	}
	else if (c->map[mody][modx] == '\0')
		return (TRUE);
	return (FALSE);
}

void	move_camera(t_config *c)
{
	float	a;
	float	step;
	float	temp;
	t_pos	moved;

	c->camera.rotation_angle += c->camera.turndirection * c->camera.turnspeed;
	step = c->camera.walkdirection * c->camera.walkspeed;
	if (c->camera.walkd_right_left != 0)
	{
		temp = c->camera.rotation_angle - c->camera.walkd_right_left * M_PI / 2;
		a = normalize(temp);
		moved.x = c->camera.x + cos(a) * step;
		moved.y = c->camera.y + sin(a) * step;
	}
	else
	{
		moved.x = c->camera.x + cos(c->camera.rotation_angle) * step;
		moved.y = c->camera.y + sin(c->camera.rotation_angle) * step;
	}
	if (!blocked(c, moved.x, moved.y))
	{
		c->camera.x = moved.x;
		c->camera.y = moved.y;
	}
}
