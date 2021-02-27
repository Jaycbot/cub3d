/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:38:34 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:39:00 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	compensate_p(t_pos *p, double width, double height)
{
	if (p->x < 0)
		p->x = 0;
	if (p->x > width)
		p->x = width - 1;
	if (p->y < 0)
		p->y = 0;
	if (p->y > height)
		p->y = height - 1;
}

int		is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (TRUE);
	return (FALSE);
}

int		ft_atoi(const char *nptr)
{
	int		ret;
	int		sign;
	char	*ascii;

	ascii = (char *)nptr;
	ret = 0;
	sign = 1;
	while (is_space(*ascii))
		++ascii;
	if (*ascii == '+' || *ascii == '-')
	{
		sign = (*ascii == '-') ? -1 : 1;
		++ascii;
	}
	while (*ascii >= '0' && *ascii <= '9')
	{
		ret = (ret * 10) + (*ascii - '0') * sign;
		++ascii;
	}
	return (ret);
}

int		to_coord(int x, int y, t_texture t)
{
	int	index;

	index = y * t.img.size_l +
		x * (t.img.bpp / 8);
	return (index);
}

void	find_direction(t_ray *ray)
{
	if (ray->isfacingdown && !ray->washitvertical)
		ray->direction = ID_NORTH;
	else if (ray->isfacingup && !ray->washitvertical)
		ray->direction = ID_SOUTH;
	else if (ray->isfacingleft && ray->washitvertical)
		ray->direction = ID_EAST;
	else
		ray->direction = ID_WEST;
}
