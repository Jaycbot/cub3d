/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:30:56 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:30:56 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		parse_color(char *line)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (is_capital(line[i]) || is_space(line[i]))
		++i;
	r = ft_atoi(line + i);
	while (is_digit(line[i]))
		++i;
	while (is_space(line[i]) || line[i] == ',')
		++i;
	g = ft_atoi(line + i);
	while (is_digit(line[i]))
		++i;
	while (is_space(line[i]) || line[i] == ',')
		++i;
	b = ft_atoi(line + i);
	if ((r > 255 || r < 0) || (g > 255 || g < 0) || ((b > 255 || b < 0)))
		error_etc("ERROR\nInvalid color");
	i = r << 16 | g << 8 | b;
	return (i);
}

int		parse_resolution(t_config *c, char *line)
{
	int	i;

	i = 0;
	if (c->width || c->height)
		error_etc("ERROR\nAlready Existing Resolution");
	while (is_capital(line[i]) || is_space(line[i]))
		++i;
	c->width = ft_atoi(&line[i]);
	while (is_digit(line[i]))
		++i;
	c->height = ft_atoi(&line[i]);
	if (c->width <= 0 || c->height <= 0)
		error_etc("ERROR\nInvalid Resolution");
	free(line);
	check_resolution(c);
	return (TRUE);
}

char	*parse_path(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]) || is_capital(line[i]))
		++i;
	return (ft_strdup(&line[i]));
}

void	set_p(t_pos *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}
