/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:23:28 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 12:51:02 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	edge_checkadd(char *row)
{
	int	i;
	
	i = 0;
	while (row[i])
	{
		if (row[i] != '1')
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int			edge_check(t_config *c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (c->map[i])
	{
		j = 0;
		if (c->map[i][j] != '1')
			return (FALSE);
		j = ft_strlen(c->map[i]);
		if (c->map[i][j - 1] != '1')
			return (FALSE);
		++i;
	}
	--i;
	if (!edge_checkadd(c->map[0]) || !edge_checkadd(c->map[i]))
		return (FALSE);
	return (TRUE);
}

void		parse_position(t_config *c, int i, int j)
{
	double	angle;
	char	dir;

	dir = c->map[i][j];
	if (dir == 'N')
		angle = M_PI * 1.5;
	else if (dir == 'S')
		angle = M_PI * 0.5;
	else if (dir == 'E')
		angle = 2 * M_PI;
	else if (dir == 'W')
		angle = M_PI;
	c->camera.rotation_angle = angle;
	c->camera.x = (j + .5) * c->tile;
	c->camera.y = (i + .5) * c->tile;
}

int			check_and_find(t_config *c)
{
	int		i;
	int		j;

	i = 0;
	if (!edge_check(c))
		return (FALSE);
	while (c->map[i])
	{
		j = 0;
		while (c->map[i][j])
		{
			if (is_in("NSWE", c->map[i][j]))
				parse_position(c, i, j);
			if (c->map[i][j] == '2')
				g_sprite_count++;
			++j;
		}
		++i;
	}
	return (TRUE);
}
