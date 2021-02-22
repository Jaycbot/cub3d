#include "../include/cub3d.h"

int	key_press(int keycode, t_config *config)
{
	if (keycode == W)
		config->camera.walkdirection = FORWARD;
	else if (keycode == S)
		config->camera.walkdirection = BACKWARD;
	else if (keycode == A)
	{
		config->camera.walkd_right_left = LEFT;
		config->camera.walkdirection = FORWARD;
	}
	else if (keycode == D)
	{
		config->camera.walkd_right_left = RIGHT;
		config->camera.walkdirection = FORWARD;
	}
	else if (keycode == KEY_RIGHT)
		config->camera.turndirection = 1;
	else if (keycode == KEY_LEFT)
		config->camera.turndirection = -1;
	else if (keycode == ESC)
	{
		free_all(config);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_config *config)
{
	if (keycode == W)
		config->camera.walkdirection = 0;
	else if (keycode == S)
		config->camera.walkdirection = 0;
	else if (keycode == A)
	{
		config->camera.walkd_right_left = 0;
		config->camera.walkdirection = 0;
	}
	else if (keycode == D)
	{
		config->camera.walkd_right_left = 0;
		config->camera.walkdirection = 0;
	}
	else if (keycode == KEY_RIGHT)
		config->camera.turndirection = 0;
	else if (keycode == KEY_LEFT)
		config->camera.turndirection = 0;
	return (0);
}