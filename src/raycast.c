#include "../include/cub3d.h"

static	int		texture_to_pixel(t_texture t, double x, double y)
{
	int			color;
	double		hop;

	hop = 0;
	color = 0;
	if (x >= 0 && x < t.width)
	{
		if (y >=0 && y < t.height)
		{
			hop = t.width * (int)y + (int)x;
			color = *(t.texture + (int)floor(hop));
		}
	}
	return (color);
}

void	restrain_pos(t_pos *pos, t_pos *size)
{
	if (pos->x < 0)
		pos->x = 0;
	if (pos->x > size->x)
		pos->x = size->x - 1;
	if (pos->y < 0)
		pos->y = 0;
	if (pos->y > size->y)
		pos->y = size->y - 1;
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
	draw_point.y = (c->height / 2) - (wall_height / 2) - 1;
	if (draw_point.y < 0)
		draw_point.y = 0;
	i = 0;
	while (i++ < wall_height && draw_point.y < c->height)
	{ 
		r_p.y = (draw_point.y - (c->height * .5 - wall_height * .5))
			/ wall_height * c->textures[ray[stripid].direction].height;
		color = texture_to_pixel(c->textures[ray[stripid].direction], r_p.x, r_p.y);
		if (color)
			c->img.data[to_coord(draw_point.x, draw_point.y, c)] = color;
		draw_point.y++;
	}
}

static	void	init_ray_info(t_config *c, t_ray *ray)
{
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->isfacingdown = TRUE;
	else
		ray->isfacingdown = FALSE;
	ray->isfacingright = ray->angle < (M_PI / 2) || ray->angle > 1.5 * M_PI;
	ray->isfacingup = !ray->isfacingdown;
	ray->isfacingleft = !ray->isfacingright;
}

void			casting(t_config *c, t_ray *ray)
{
	double	distance_v;
	double	distance_h;
	t_pos	hit_v;
	t_pos	hit_h;

	init_ray_info(c, ray);
	hit_h = wall_hit_h(c, ray, ray->angle);
	hit_v = wall_hit_v(c, ray, ray->angle);
	distance_v = hypot(c->camera.x  - hit_v.x, c->camera.y - hit_v.y);
	distance_h = hypot(c->camera.x - hit_h.x, c->camera.y - hit_h.y);
	if (distance_v < distance_h)
	{
		ray->actual_dist = distance_v * cos(ray->angle - c->camera.rotation_angle);
		ray->hit_p = hit_v;
		ray->washitvertical = TRUE;
	}
	else
	{
		ray->actual_dist = distance_h * cos(ray->angle - c->camera.rotation_angle);
		ray->hit_p = hit_h;
		ray->washitvertical = FALSE;
	}
	find_direction(ray);
}

void			raycast(t_config *c)
{
	t_ray	*rays;
	int		stripid;
	double	angle;

	stripid = 0;
	if (!(rays = (t_ray *)malloc(sizeof(t_ray) * c->width)))
		error_etc("ERROR\nMalloc failed");
	angle = c->camera.rotation_angle - (c->fov / 2);
	c->dist_to_plane = (c->width / 2) / tan(c->fov / 2);
	while (stripid < c->width)
	{
		rays[stripid].angle = normalize(angle);
		casting(c, &rays[stripid]);
		// if (rays[stripid].isfacingdown)
		// 	printf("%d is facing down\n", stripid);
		// if (rays[stripid].isfacingup)
		// 	printf("%d is facing up\n", stripid);
		// if (rays[stripid].isfacingright)
		// 	printf("%d is facing right\n", stripid);
		// if (rays[stripid].isfacingleft)
		// 	printf("%d is facing left\n", stripid);
		// printf("%d direction is %d \n", stripid, rays[stripid].direction);
		draw(c, rays, stripid);
		angle += (c->fov / c->width);
		++stripid;
	}
	free(rays);
}