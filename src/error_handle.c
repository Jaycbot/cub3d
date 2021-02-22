#include "../include/cub3d.h"

void	error_with_message(char *prefix)
{
	perror(prefix);
	exit(EXIT_FAILURE);
}

void	error_etc(char *msg)
{
	printf("%s\n", msg);
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
	i = 0;
	while (i < 5)
	{
		if (c->textures[i].texture)
			free(c->textures[i].texture);
		++i;
	}
}