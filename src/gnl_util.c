#include "../include/cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		++i;
	return (i);
}

char	*ft_strdup(char *str)
{
	size_t	size;
	char	*ret;

	size = ft_strlen(str);
	if (!(ret = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	size = 0;
	while (str[size])
	{
		ret[size] = str[size];
		++size;
	}
	ret[size] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (ft_strdup(""));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	max;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	max = ft_strlen(str);
	if (start >= max)
		return (ft_strdup(""));
	if (!(substr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = start;
	j = 0;
	while (str[i] && j < len)
		substr[j++] = str[i++];
	substr[j] = '\0';
	return (substr);
}

int		is_in(char *s, int c)
{
	int i;

	i = 0;
	if (!c)
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}