/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:36:09 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:38:10 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	transform_to_texture(t_config *c, t_ray *ray, int stripid)
{
	double	ret;
	double	unit_distance;
	t_ray	r;

	r = ray[stripid];
	if (ray[stripid].washitvertical)
		unit_distance = (int)fmod(r.hit_p.y, c->tile);
	else
		unit_distance = (int)fmod(r.hit_p.x, c->tile);
	ret = unit_distance / c->tile * c->textures[r.direction].img.img_w;
	return (ret);
}

double	normalize(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int		is_inside_map(t_config *c, double x, double y)
{
	if (x > 0 && x < c->width && y > 0 && y < c->height)
		return (TRUE);
	return (FALSE);
}

t_pos	wall_hit_v(t_config *c, t_ray *ray, double angle)
{
	t_pos	intercept;
	t_pos	to_check;
	t_pos	next_touch;
	double	step_x;
	double	step_y;

	intercept.x = floor(c->camera.x / c->tile) * c->tile;
	if (ray->isfacingright)
		intercept.x += c->tile;
	intercept.y = c->camera.y + (intercept.x - c->camera.x) * tan(angle);
	step_x = c->tile * (ray->isfacingleft ? -1 : 1);
	step_y = c->tile * tan(angle);
	step_y *= ((ray->isfacingup && step_y > 0) ||
		(ray->isfacingdown && step_y < 0)) ? -1 : 1;
	set_p(&next_touch, intercept.x, intercept.y);
	while (is_inside_map(c, next_touch.x, next_touch.y))
	{
		set_p(&to_check, next_touch.x +
			(ray->isfacingleft ? -1 : 0), next_touch.y);
		if (blocked(c, to_check.x, to_check.y))
			return (next_touch);
		set_p(&next_touch, next_touch.x + step_x, next_touch.y + step_y);
	}
	compensate_p(&next_touch, c->width, c->height);
	return (next_touch);
}

t_pos	wall_hit_h(t_config *c, t_ray *ray, double angle)
{
	t_pos	intercept;
	t_pos	to_check;
	t_pos	next_touch;
	double	step_x;
	double	step_y;

	intercept.y = floor(c->camera.y / c->tile) * c->tile;
	if (ray->isfacingdown)
		intercept.y += c->tile;
	intercept.x = c->camera.x + (intercept.y - c->camera.y) / tan(angle);
	step_x = c->tile / tan(angle);
	step_y = c->tile * (ray->isfacingup ? -1 : 1);
	if ((ray->isfacingleft && step_x > 0) || (ray->isfacingright && step_x < 0))
		step_x *= -1;
	set_p(&next_touch, intercept.x, intercept.y);
	while (is_inside_map(c, next_touch.x, next_touch.y))
	{
		set_p(&to_check, next_touch.x, next_touch.y
			+ (ray->isfacingup ? -1 : 0));
		if (blocked(c, to_check.x, to_check.y))
			return (next_touch);
		set_p(&next_touch, next_touch.x + step_x, next_touch.y + step_y);
	}
	compensate_p(&next_touch, c->width, c->height);
	return (next_touch);
}
