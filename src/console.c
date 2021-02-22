#include "../include/cub3d.h"

int		blocked(t_config *c, double x, double y)
{
	int	deltaX;
	int	deltaY;

	if (x < 0 || x > c->cols * c->tile || y < 0 || y > c->height)
		return (1);
	deltaX = (int)floor(x / c->tile);
	deltaY = (int)floor(y / c->tile);
	if (deltaX <= 0 || deltaX >= c->cols || deltaY <= 0 || deltaY >= c->rows)
		return (1);
	if (c->map[deltaY][deltaX] == '1' || c->map[deltaY][deltaX] == '2')
	{
		if (c->map[deltaY][deltaX] == '1')
			return (1);
		if (c->map[deltaY][deltaX] == '2')
			return (2);
	}
	else if (c->map[deltaY][deltaX] == '\0')
		return (TRUE);
	return (FALSE);
}

void	move_camera(t_config *c)
{
	float	angle;
	float	step;
	t_pos	moved;

	c->camera.rotation_angle += c->camera.turndirection * c->camera.turnspeed;
	step = c->camera.walkdirection * c->camera.walkspeed;
	if (c->camera.walkd_right_left)
	{
		angle = normalize(c->camera.rotation_angle - c->camera.walkd_right_left * M_PI / 2);
		moved.x = c->camera.x + cos(angle) * step;
		moved.y = c->camera.y + sin(angle) * step;
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