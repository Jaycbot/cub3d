#include "../include/cub3d.h"

static	void	converter(unsigned char *buf, int value)
{
	buf[0] = (unsigned char)value;
	buf[1] = (unsigned char)(value >> 8);
	buf[2] = (unsigned char)(value >> 16);
	buf[3] = (unsigned char)(value >> 24);
}

void	save_bmp_format(t_config *c)
{
	int	fd;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 644);
	if (fd == -1)
		error_etc("ERROR\nCan't make bmp file");
	move_camera(c);
	raycast(c, c->rays);
	render_sprites(c);
	mlx_put_image_to_window(c->mlx, c->win.win,
		c->img.img, 0, 0);
}