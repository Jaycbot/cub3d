/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:31:24 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 13:22:13 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	void	save_wall_info(t_config *c, t_ray *ray, double wall_h)
{
	double	top;
	double	bottom;

	top = (c->height / 2) - ((int)wall_h / 2);
	if (top < 0)
	top = 0;
	bottom = (c->height / 2) + ((int)wall_h / 2);
	ray->top_strip = top;
	ray->bottom_strip = bottom;
}

void			draw(t_config *c, t_ray *ray, int stripid)
{
	int		color;
	int		i;
	double	wall_height;
	t_pos	r_p;
	t_pos	draw_point;

	r_p.x = transform_to_texture(c, ray, stripid);
	wall_height = c->tile * (c->dist_to_plane / ray[stripid].actual_dist);
	draw_point.x = stripid;
	draw_point.y = (c->height / 2) - (wall_height / 2);
	if (draw_point.y < 0)
		draw_point.y = 0;
	i = 0;
	save_wall_info(c, &ray[stripid], wall_height);
	while (i++ < wall_height && ++draw_point.y < c->height)
	{
		r_p.y = (draw_point.y - (c->height / 2 - wall_height / 2))
			/ wall_height * c->textures[ray[stripid].direction].img.img_h;
		color = pick_pixel(&c->textures[ray[stripid].direction].img,
			r_p.x, r_p.y);
		if (color)
			insert_pixel(&c->img, draw_point.x, draw_point.y, color);
	}
}

static	void	init_ray_info(t_config *c, t_ray *ray)
{
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->isfacingdown = TRUE;
	else
		ray->isfacingdown = FALSE;
	ray->isfacingright = ray->angle < (M_PI_2) || ray->angle > (1.5 * M_PI);
	ray->isfacingup = !ray->isfacingdown;
	ray->isfacingleft = !ray->isfacingright;
}

void			casting(t_config *c, t_ray *ray, int id)
{
	double	dist_v;
	double	dist_h;
	t_pos	hit_v;
	t_pos	hit_h;

	init_ray_info(c, ray);
	hit_h = wall_hit_h(c, ray, ray->angle);
	hit_v = wall_hit_v(c, ray, ray->angle);
	dist_v = hypot(c->camera.x - hit_v.x, c->camera.y - hit_v.y);
	dist_h = hypot(c->camera.x - hit_h.x, c->camera.y - hit_h.y);
	if (dist_v < dist_h)
	{
		ray->actual_dist = dist_v * cos(ray->angle - c->camera.rotation_angle);
		ray->hit_p = hit_v;
		ray->washitvertical = TRUE;
	}
	else
	{
		ray->actual_dist = dist_h * cos(ray->angle - c->camera.rotation_angle);
		ray->hit_p = hit_h;
		ray->washitvertical = FALSE;
	}
	find_direction(ray);
}

void			raycast(t_config *c, t_ray * rays)
{
	int		stripid;
	double	angle;

	stripid = 0;
	angle = c->camera.rotation_angle - (c->fov / 2);
	c->dist_to_plane = (c->width / 2) / tan(c->fov / 2);
	while (stripid < c->width)
	{
		rays[stripid].angle = normalize(angle);
		casting(c, &rays[stripid], stripid);
		draw(c, rays, stripid);
		angle += (c->fov / c->width);
		print_ceiling(c, &rays[stripid], stripid);
		print_floor(c, &rays[stripid], stripid);
		++stripid;
	}
}