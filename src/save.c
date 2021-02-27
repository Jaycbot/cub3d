#include "../include/cub3d.h"

static	void	converter(unsigned char *buf, unsigned int value)
{
	buf[0] = (unsigned char)(value);
	buf[1] = (unsigned char)(value >> 8);
	buf[2] = (unsigned char)(value >> 16);
	buf[3] = (unsigned char)(value >> 24);
}

static	void	write_bmp_body(t_config *c, t_bmp *bmp, int fd)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = c->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < c->width)
		{
			bmp->body[i] = pick_pixel(&c->img, x, y);
			++i;
			++x;
		}
		--y;
	}
	if (!(write(fd, &bmp->body[0], c->height * c->width * 4)))
		error_etc("ERROR\nCan't make bmp file", c);
}

static	void	write_bmp_header(t_config *c, t_bmp *bmp, int fd)
{
	unsigned int	size;
	int				i;

	ft_memset(&bmp->header, 0, 54);
	size = c->width * c->height * (c->img.bpp / 8) + 54;
	bmp->header[0] = (unsigned char)0x42;
	bmp->header[1] = (unsigned char)0x4D;
	converter(&bmp->header[2], size);
	bmp->header[10] = (unsigned char)0x36;
	bmp->header[14] = (unsigned char)0x28;
	converter(&bmp->header[18], c->width);
	converter(&bmp->header[22], c->height);
	bmp->header[26] = (unsigned char)0x1;
	converter(&bmp->header[28], c->img.bpp);
	i = write(fd, &bmp->header, 54);
	if (!i)
		error_etc("ERROR\nCan't make bmp file", c);
}

void	save_bmp_format(t_config *c)
{
	int	fd;

	fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_etc("ERROR\nCan't make bmp file",c);
	raycast(c, c->rays);
	render_sprites(c);
	write_bmp_header(c, &c->bmp, fd);
	write_bmp_body(c, &c->bmp, fd);
	close(fd);
	free_all(c);
	exit(0);
}
