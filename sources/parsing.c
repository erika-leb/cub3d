/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:55 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_first_part(char *line, t_data *data, t_gc *gc)
{
	int		r;

	while (line != NULL && data->flag == 0)
	{
		data->i = 0;
		line = get_next_line(data->fd, data, gc);
		ft_lose_space(line, &data->i);
		r = ft_check_if_texture(&data->i, line);
		if (r == 9)
			return (1);
		if (r == 0)
		{
			printf("Error: Missing texture or color\n");
			return (1);
		}
		if (r == 8)
			data->flag = 1;
		ft_lose_space(line, &data->i);
		if (r != 7 && ft_process_data(r, line, data, gc) == 1)
			return (1);
		(data->lg)++;
	}
	return (0);
}

// int	ft_get_map(char *line, t_data *data) //prevoir le cas ou il n'y a pas de map
// {
// 	while (line != NULL)
// 	{
// 		data->i = 0;
// 		ft_lose_space(line, &data->i);
// 		if ()
// 	}
// 	return (0);
// }

int	ft_get_data(int fd, t_data *data, t_gc *gc)
{
	char	*line;

	line = ft_strdup_bis("", gc);
	data->i = 0;
	if (ft_first_part(line, data, gc) == 1)
		return (1);
	// while (line != NULL && data->flag == 0)
	// {
	// 	data->i = 0;
	// 	line = get_next_line(fd, data, gc);
	// 	ft_lose_space(line, &data->i);
	// 	r = ft_check_if_texture(&data->i, line);
	// 	if (r == 9)
	// 		return (1);
	// 	if (r == 0)
	// 	{
	// 		printf("Error: Missing texture or color\n");
	// 		return (1);
	// 	}
	// 	if (r == 8)
	// 		data->flag = 1;
	// 	ft_lose_space(line, &data->i);
	// 	if (r != 7 && ft_process_data(r, line, data, gc) == 1)
	// 		return (1);
	// 	(data->l)++;
	// }
	// if (ft_get_map(line, data) == 1)
	// 	return (1);
	if (ft_check_walls(data, gc) == 1)
		return (1);
	return (0);
}

int	ft_parsing(char **argv, t_data *data, t_gc *gc)
{
	if (!argv[1])
	{
		write(2, "Error: No file found\n", 22);
		return (1);
	}
	if (ft_check_extention(argv[1]) == 1)
	{
		// write(2,"Error: No .cub file found\n", 27);
		write(2,"Error: Wrong filetype\n", 23);
		return (1);
	}
	data->fd = open(argv[1], O_RDONLY);
	if (data->fd == -1)
	{
		perror("Error while opening file");
		return (1);
	}
	if (ft_get_data(data->fd, data, gc) == 1)
		return (close(data->fd), (1));
	close(data->fd);
	return (0);
}
