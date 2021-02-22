#include "../include/cub3d.h"

void	fill_floor_ceiling(t_config *c)
{
	int			x;
	int			y;
	int			height;
	int			width;

	height = c->height;
	width = c->width;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			c->img.data[y * width + x] = c->color_f;
			c->img.data[(height - y - 1) * width + x] = c->color_c;
			x++;
		}
		++y;
	}
}

int		*texture_img(t_config *c, int index, t_img *img)
{
	int		*pixels;
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(c->mlx, c->textures[index].path, &img->img_w, &img->img_h);
	if (!img->img)
		error_etc("ERROR\nInvalid Texture path");
	c->textures[index].width = img->img_w;
	c->textures[index].height = img->img_h;
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	if (!(pixels = (int *)malloc(sizeof(int) * img->img_w * img->img_h)))
		error_etc("ERROR\nMalloc failed");
	y = 0;
	while (y < img->img_h)
	{
		x = 0;
		while (x++ < img->img_w)
			pixels[y * img->img_w + x] = img->data[y * img->img_w + x];
		++y;
	}
	mlx_destroy_image(c->mlx, img->img);
	return (pixels);
}

void	parse_texture(t_config *c)
{
	int		i;
	t_img	img;
	
	i = 0;
	while (i < 5)
	{
		c->textures[i].texture = texture_img(c, i, &img);
		free(c->textures[i].path);
		c->textures[i].path = NULL;
		++i;
	}
}