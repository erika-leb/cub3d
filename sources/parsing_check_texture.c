/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 17:55:31 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_check_files(t_data *data)
{
	int	fd;

	fd = open(data->ea, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->no, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->we, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->so, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	ft_check_walls(t_data *data, t_gc *gc)
{
	if (data->no == NULL || data->so == NULL || data->we == NULL
		|| data->ea == NULL || data->c == NULL || data->f == NULL)
	{
		printf("Error\nMissing texture or color\n");
		return (1);
	}
	// printf("ea = %si\n", data->ea);
	// printf("no = %si\n", data->no);
	// printf("so = %si\n", data->so);
	// printf("we = %si\n", data->we);
	if (ft_xpm_extention(data->no) == 1 || ft_xpm_extention(data->so) == 1
		|| ft_xpm_extention(data->we) == 1 || ft_xpm_extention(data->ea) == 1)
	{
		printf("Error\nWrong texture extention\n");
		return (1);
	}
	if (ft_check_color(data, gc) == 1)
	{
		printf("Error\nWrong color data\n");
		return (1);
	}
	if (ft_check_files(data) == 1)
	{
		printf("Error\nProblem while opening xpm file\n");
		return (1);
	}
	return (0);
}
