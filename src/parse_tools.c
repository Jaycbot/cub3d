/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:30:15 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:30:17 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	empty_line_check(char *line)
{
	while (*line && is_space(*line))
		++line;
	if (*line == '\0')
		return (TRUE);
	return (FALSE);
}

int	extenstion_check(char *filename)
{
	int	file_len;
	int	i;

	file_len = ft_strlen(filename);
	if (file_len <= 4)
		return (FALSE);
	i = file_len - 4;
	if (is_equal(filename + i, ".cub"))
		return (TRUE);
	return (FALSE);
}

int	contents_check(char *line)
{
	while (*line)
	{
		if (is_in(MAP_COMPONENTS, *line))
		{
			check_double_position(*line);
			++line;
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

int	is_capital(char c)
{
	return ((c >= 65 && c <= 90) ? 1 : 0);
}

int	identifier_check(char *line, t_config *c)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (ID_RESOLUTION);
	else if (line[0] == 'N' && line[1] == 'O')
		return (ID_NORTH);
	else if (line[0] == 'S' && line[1] == 'O')
		return (ID_SOUTH);
	else if (line[0] == 'W' && line[1] == 'E')
		return (ID_WEST);
	else if (line[0] == 'E' && line[1] == 'A')
		return (ID_EAST);
	else if (line[0] == 'S' && line[1] == ' ')
		return (ID_SPRITE);
	else if (line[0] == 'F' && line[1] == ' ')
		return (ID_FLOOR);
	else if (line[0] == 'C' && line[1] == ' ')
		return (ID_CEILING);
	else if (contents_check(line))
		return (ID_MAP);
	if (g_camera_count != 1)
		error_etc("ERROR\nInvalid camera positions in the map", c);
	return (-1);
}
