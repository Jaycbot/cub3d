/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:18:54 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:18:58 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	error_with_message(char *prefix)
{
	perror(prefix);
	exit(EXIT_FAILURE);
}

void	error_etc(char *msg, t_config *c)
{
	printf("%s\n", msg);
	free_all(c);
	exit(EXIT_FAILURE);
}

int		free_line(char *line)
{
	if (line)
	{
		free(line);
		return (TRUE);
	}
	return (FALSE);
}
static	void	free_add(t_config *c)
{
	if (c->textures[0].img.img)
		mlx_destroy_image(c->mlx, c->textures[0].img.img);
	if (c->textures[1].img.img)
		mlx_destroy_image(c->mlx, c->textures[1].img.img);
	if (c->textures[2].img.img)
		mlx_destroy_image(c->mlx, c->textures[2].img.img);
	if (c->textures[3].img.img)
		mlx_destroy_image(c->mlx, c->textures[3].img.img);
	if (c->textures[4].img.img)
		mlx_destroy_image(c->mlx, c->textures[4].img.img);
}
void	free_all(t_config *c)
{
	int i;

	i = 0;
	if (c->map[i] && c->map)
	{
		while (c->map[i])
			free_line(c->map[i++]);
		free(c->map);
	}
	if (c->rays)
		free(c->rays);
	if (c->sprites)
		free(c->sprites);
	free_add(c);
}
