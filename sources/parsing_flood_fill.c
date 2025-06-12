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
	perror("deuxieme");
    while (data->map[k])
    {
        printf("%s\n", data->map[k]);
        k++;
    }
}

int ft_flood_fill(t_data *data, t_gc *gc)
{
    ft_copy_map(data, gc);
    return (0);
}