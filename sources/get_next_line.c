/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:37 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/02 20:11:59 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_free(char *s)
{
	free(s);
	s = NULL;
	return (s);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	while (s && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*clean_stash_buffer(char *stash, char *buffer, int *n)
{
	int		i;
	int		j;
	char	*temp;

	i = ft_strchr(buffer, '\n');
	j = ft_strchr(stash, '\n');
	if (j != -1)
	{
		temp = ft_substr(stash, j + 1, ft_strlen(stash) - j - 1);
		ft_free(stash);
		stash = ft_strdup(temp);
		return (ft_free(temp), ft_free(buffer), stash);
	}
	else
	{
		if (stash != NULL)
			ft_free(stash);
		stash = NULL;
		if (i != -1)
			stash = ft_substr(buffer, i + 1, *n - i - 1);
		if (*n == 0 && stash && (stash[0] == '\0' || stash[0] == '\n')) // 🔥 Libère stash vide
			ft_free(stash); // je sais pas si c est utile
		return (ft_free(buffer), stash);
	}
}

char	*read_and_stock(int fd, char *line, char *buffer, int *n)
{
	int			i;
	int			f;
	char		*temp;
	char		*tmp;

	i = -1;
	while (i == -1 && *n == BUFFER_SIZE && ft_strchr(line, '\n') == -1)
	{
		*n = read(fd, buffer, BUFFER_SIZE);
		if (*n == -1)
			return (NULL);
		i = ft_strchr(buffer, '\n');
		f = (*n);
		if (*n != 0)
		{
			if (i != -1)
				f = i + 1;
			tmp = ft_substr(buffer, 0, f);
			temp = ft_strdup(line);
			ft_free(line);
			line = ft_strjoin(temp, tmp);
			(ft_free(temp), ft_free(tmp));
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash = NULL;
	char		*line;
	int			n;

	if (fd == -1 || BUFFER_SIZE < 0 || read(fd, stash, 0) < 0)
	{
		if (stash != NULL)
			stash = ft_free(stash);
		return (NULL);
	}
	n = BUFFER_SIZE;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	line = NULL;
	if (stash != NULL && stash[0] != '\0' && ft_strchr(stash, '\n') == -1)
		line = ft_strdup(stash);
	else if (stash != NULL && stash[0] != '\0' && ft_strchr(stash, '\n') != -1)
		line = ft_substr(stash, 0, ft_strchr(stash, '\n') + 1);
	line = read_and_stock(fd, line, buffer, &n);
	stash = clean_stash_buffer(stash, buffer, &n);
	// printf("clean_stash_buffer -> new stash: %sg\n", stash);
	return (line);
}
