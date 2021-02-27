/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <jaehchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:24:31 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 13:15:12 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*trim_cols(char *row, t_config *c)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = trimmed_size(row);
	if (!(trimmed = (char *)malloc(sizeof(char) * (j + 1))))
		error_etc("ERROR\nMalloc Failed", c);
	j = 0;
	while (row[i])
	{
		if (!is_space(row[i]))
		{
			trimmed[j] = row[i];
			++j;
			++i;
			continue ;
		}
		++i;
	}
	trimmed[j] = '\0';
	free(row);
	return (trimmed);
}

int		parse_map(t_config *c, char *line)
{
	int	rows;
	int	cols;
	int	temp;

	rows = 0;
	cols = 0;
	c->map = ft_split(line, '\n');
	if (!c->map)
		error_etc("ERROR\nMalloc Faild", c);
	free(line);
	while (c->map[rows])
	{
		c->map[rows] = trim_cols(c->map[rows], c);
		temp = ft_strlen(c->map[rows]);
		if (cols != temp)
			cols = max(cols, temp);
		++rows;
	}
	c->rows = rows;
	c->cols = cols;
	c->tile = c->width / c->cols;
	return (TRUE);
}

int		parse_by_id(t_config *c, int id, char *line)
{
	if (id == ID_RESOLUTION)
		return (parse_resolution(c, line));
	else if (id >= 0 && id <= 4)
	{
		if (c->textures[id].path)
			error_etc("ERROR\nAlready Exist path", c);
		c->textures[id].path = parse_path(line);
	}
	else if (id == ID_FLOOR || id == ID_CEILING)
	{
		if (id == ID_FLOOR)
		{
			if (c->color_f)
				error_etc("ERROR\nAlready Exist path", c);
			c->color_f = parse_color(line, c);
		}
		else
		{
			if (c->color_c)
				error_etc("ERROR\nAlready Exist path", c);
			c->color_c = parse_color(line, c);
		}
	}
	return (free_line(line));
}

int		parse_file_lines(t_config *c, int fd)
{
	int			read_b;
	int			id;
	static char	*rem;
	char		*line;

	read_b = 1;
	while ((read_b = get_next_line(fd, &line)) > 0)
	{
		if ((id = identifier_check(line, c)) == -1)
			error_etc("ERROR\nWrong Identifier", c);
		if (empty_line_check(line))
		{
			free_line(line);
			continue ;
		}
		if (id == ID_MAP)
		{
			rem = bridge(&rem, line);
			free(line);
			rem = bridge(&rem, "\n");
		}
		else
			parse_by_id(c, id, line);
	}
	return (parse_map(c, rem));
}

int		parse_file(t_config *c, char *filepath)
{
	int	fd;

	if (!extenstion_check(filepath))
		error_etc("ERROR\nInvalid extention", c);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		error_etc("ERROR\nNo such file or invalid filepath", c);
	parse_file_lines(c, fd);
	close(fd);
	return (TRUE);
}
