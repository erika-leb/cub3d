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

int	ft_type_line(char *line)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || line[i] == '0' || line[i] == '1' ||
				line[i] == 'N' || line[i] == 'S' || line[i] == 'E' ||
				line[i] == 'W' || (line[i] >= 9 && line[i] <= 13)))
		{
			printf("Error: invalid line\n");
			return (2); //quitter
		}
		if (line[i] == '1' || line[i] == '0')
			f = 1;
		i++;
	}
	// printf("f = %d\n", f);
	return (f);
}

int ft_reinit_fd(t_data *data, t_gc *gc)
{
    int i;

    close(data->fd);
	data->fd = open(data->arg, O_RDONLY);
	if (data->fd == -1)
	{
		perror("Error while opening file");
		return (1);
	}
	i = 0;
	while (i < data->start)
	{
		data->line = get_next_line(data->fd, data, gc);
		i++;
	}
    return (0);
}

int ft_manage_line(int n, int *f)
{
	if (n == 2)
		return (1);
	if (n == 0)
		(*f) = 1;
	if (n == 1 && (*f) == 1)
	{
		printf("Error: Empty line in map\n");
		return (1);
	}
    return (0);
}

int	ft_arr_size(t_data *data, t_gc *gc)
{
	int	max;
	int	s;
	int	n;
	int	f;

	max = 0;
	data->start = data->lg;
	data->lg = 0;
	f = 0;
	while (data->line != NULL)
	{
		s = 0;
		while (data->line[s] && data->line[s] != '\n')
			s++;
		if (s > max)
			max = s;
		n = ft_type_line(data->line);
        if (ft_manage_line(n, &f) == 1)
            return (1);
		// if (n == 2)
		// 	return (1);
		// if (n == 0)
		// 	f = 1;
		// if (n == 1 && f == 1)
		// {
		// 	printf("Error: Empty line in map\n");
		// 	return (1);
		// }
		else if (n == 1)
			(data->lg)++;
		// printf("ligne = %s\n", data->line);
		// printf("nb lines = %d\n", data->lg);
		data->line = get_next_line(data->fd, data, gc);
	}
	data->cl = max;
    if (ft_reinit_fd(data, gc) == 1)
        return (1);
	// printf("nbre colonnes = %d\n", data->cl);
	// printf("nbre lignes = %d\n", data->lg);
	// printf("ligne fin = %s\n", data->line);
	return (0);
}

void	ft_get_map(t_data *data, t_gc *gc)
{
	int	i;
	int	k;

	k = 0;
	data->map = gc_malloc(sizeof(char *) * (data->lg + 1), gc);
	while (data->line != NULL)
	{
		i = 0;
		if (ft_type_line(data->line) == 0)
			break ;
		data->map[k] = gc_malloc(sizeof(char) * (data->cl + 1), gc);
		while (data->line[i] && data->line[i] != '\n')
		{
			if (ft_is_space(data->line[i]) == 1)
				data->map[k][i] = '1';
			else
				data->map[k][i] = data->line[i];
			i++;
		}
		while (i < data->cl)
		{
			data->map[k][i] = '1';
			i++;
		}
		data->map[k][i] = '\0';
		k++;
		data->line = get_next_line(data->fd, data, gc);
	}
	data->map[k] = NULL;
    k = 0;
    while (data->map[k])
    {
        printf("%s\n", data->map[k]);
        k++;
    }
}
