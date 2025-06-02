/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/05/29 17:21:45 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = s;
	if (s == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*str;
	int		k;

	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 != NULL && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	k = 0;
	while (s2 != NULL && s2[k])
		str[i++] = s2[k++];
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return ("");
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (NULL);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(size_t n, size_t sizof)
{
	unsigned char	*buffer;
	size_t			i;

	if (n < 1 || sizof < 1 || n > SIZE_MAX / sizof)
		return (NULL);
	i = 0;
	buffer = malloc(n * sizof);
	if (buffer == NULL)
		return (NULL);
	while (i < n * sizof)
		buffer[i++] = (unsigned char)0;
	return (buffer);
}
