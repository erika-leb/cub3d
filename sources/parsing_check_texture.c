/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/02 19:19:33 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_xpm_extention(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	// printf("s[i] = %c\n", s[i]);
	// printf("s[i - 1] = %c\n", s[i - 1]);
	// printf("s[i - 2] = %c\n", s[i - 2]);
	// printf("s[i - 3] = %c\n", s[i - 3]);
	// printf("s[i - 4] = %c\n", s[i - 4]);
	if (i < 5)
		return (1);
	if (s[i - 1] != 'm')
		return (1);
	if (s[i - 2] != 'p')
		return (1);
	if (s[i - 3] != 'x')
		return (1);
	if (s[i - 4] != '.')
		return (1);
	return (0);
}

int	ft_check_color(t_data *data)
{
	(void) data;
	return (0);
}

int	ft_check_walls(t_data *data, t_gc *gc)
{

		(void) gc;
	// printf("no = %si\n", data->no);
	// printf("so = %si\n", data->so);
	// printf("we = %si\n", data->we);
	// printf("ea = %si\n", data->ea);
	// printf("c = %si\n", data->c);
	// printf("f = %si\n", data->f);

	//ouvrir et verifier la presence des fichiers, checker les couleurs
	// verifier si typefile est bien xml ou autre ?
	if (data->no == NULL || data->so == NULL || data->we == NULL || data->ea == NULL || data->c == NULL || data->f == NULL)
	{
		printf("Error: Missing texture or color\n");
		return (1);
	}
	if (ft_xpm_extention(data->no) == 1 || ft_xpm_extention(data->so) == 1 || ft_xpm_extention(data->we) == 1 || ft_xpm_extention(data->ea) == 1)
	{
		printf("Error: wrong texture extention\n");
		return (1);
	}
	if (ft_check_color(data) == 1)
	{
		printf("Error: Wrong color data\n");
		return (1);
	}
	return (0);
}
