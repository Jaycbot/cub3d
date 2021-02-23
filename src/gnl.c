/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:19:11 by jaehchoi          #+#    #+#             */
/*   Updated: 2021/02/23 11:19:13 by jaehchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		find_new_line(char *s)
{
	int	index;

	index = 0;
	while (*s)
	{
		if (*s == '\n')
			return (index);
		++index;
		++s;
	}
	return (-1);
}

char	*bridge(char **backup, char *to_add)
{
	char	*temp;

	if (*backup != NULL)
	{
		temp = ft_strjoin(*backup, to_add);
		free(*backup);
		*backup = temp;
	}
	else
		*backup = ft_strdup(to_add);
	return (*backup);
}

void	save_n_free(char **backup, char **line, int i)
{
	char	*temp;
	size_t	left;

	*line = ft_substr(*backup, 0, i);
	left = ft_strlen(*backup + i + 1);
	if (left == 0)
	{
		free(*backup);
		*backup = NULL;
	}
	else
	{
		temp = ft_strdup(*backup + i + 1);
		free(*backup);
		*backup = temp;
	}
}

int		helper(char **backup, int read_bytes, char **line)
{
	int index;

	if (read_bytes < 0)
		return (-1);
	if (*backup != NULL)
	{
		if ((index = find_new_line(*backup)) >= 0)
		{
			save_n_free(backup, line, index);
			return (1);
		}
		*line = *backup;
		*backup = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*backup;
	int			read_bytes;
	int			cursor;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((read_bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_bytes] = '\0';
		backup = bridge(&backup, buffer);
		if ((cursor = find_new_line(backup)) >= 0)
		{
			save_n_free(&backup, line, cursor);
			free(buffer);
			return (1);
		}
	}
	free(buffer);
	cursor = helper(&backup, read_bytes, line);
	return (cursor);
}
