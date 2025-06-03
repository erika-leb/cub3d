/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/02 20:35:22 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_data	*ft_init(t_gc *gc)
{
	t_data	*data;

	data = NULL;
	data = gc_malloc(sizeof(t_data), gc);
	data->f = NULL;
	data->c = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->no = NULL;
	data->we = NULL;
	data->map = NULL;
	data->flag = 0;
	data->ceiling = NULL;
	data->floor = NULL;
	return (data);
}

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_gc	gc;

	(void) env;
	(void) argc;
	gc_init(&gc);
	data = NULL;
	data = ft_init(&gc);
	if (ft_parsing(argv, data, &gc) == 1)
	{
		gc_cleanup(&gc);
		return (1);
	}
	gc_cleanup(&gc);
	return (0);
}
