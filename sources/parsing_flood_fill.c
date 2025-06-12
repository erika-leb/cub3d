/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/12 16:09:50 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//penser au cas avec une seule ligne ou une seule colonne a tester

void	ft_copy_map(t_data *data, t_gc *gc)
{
	int	k;
	int	i;

	k = 0;
	data->m = gc_malloc(sizeof(char *) * (data->lg + 1), gc);
	while (k < data->lg)
	{
		i = 0;
		data->m[k] = gc_malloc(sizeof(char) * (data->cl + 1), gc);
		while (data->map[k][i] && data->map[k][i] != '\n')
		{
			data->m[k][i] = data->map[k][i];
			i++;
		}
		data->m[k][i] = '\0';
		k++;
	}
    data->map[k] = NULL;
    k = 0;
	// perror("deuxieme");
    // while (data->m[k])
    // {
    //     printf("%s\n", data->m[k]);
    //     k++;
    // }
}

int	ft_is_closed(t_data *data)
{
	int	c;
	int	l;

	l = -1;
	while (++l < data->lg)
	{
		c = 0;
		if (l == 0 || l == data->lg - 1) //premiere et derniere ligne
		{
			while (data->map[l][c])
			{
				if (data->map[l][c] == '0')
					return (1);
				c++;
			}
		}
		while (ft_is_space(data->m[l][c]) == 1)
			c++;
		if (data->m[l][c] == '0')
			return (1);
		c = data->cl - 1;
		while (ft_is_space(data->m[l][c]) == 1)
			c--;
		if (data->m[l][c] == '0')
			return (1);
		// l++;
	}
	return (0);
}

int	ft_get_pos(t_data *data)
{
	int	f;
	int	l;
	int	c;

	f = 0;
	l = 0;
	while (l < data->lg)
	{
		c = 0;
		while (c < data->cl)
		{
			if ((data->map[l][c] == 'S' || data->map[l][c] == 'E' || data->map[l][c] == 'W'
					|| data->map[l][c] == 'N') && f == 1)
			{
				printf("Error: multiple players\n");
				return (1);
			}
			if (data->map[l][c] == 'S' || data->map[l][c] == 'E' || data->map[l][c] == 'W'
					|| data->map[l][c] == 'N')
			{
				f = 1;
				data->pos_c = c;
				data->pos_l = l;
				data->pos = data->map[l][c];
			}
			// printf("or if c = %d\n", c);
			c++;
		}
		l++;
	}
	if (f == 0)
	{
		printf("Error: no player\n");
		return (1);
	}
	return (0);
}

int	ft_flood_fill(t_data *data, t_gc *gc)
{
	ft_copy_map(data, gc);
	if (ft_is_closed(data) == 1)
	{
		printf("Error: map not closed\n");
		return (1);
	}
	if (ft_get_pos(data) == 1)
		return (1);
	// printf("pos = %c, l = %d, c = %d\n", data->pos, data->pos_l, data->pos_c);
	return (0);
}
