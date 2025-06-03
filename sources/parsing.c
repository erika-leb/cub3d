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

int	ft_get_data(int fd, t_data *data, t_gc *gc)
{
	char	*line;
	int		r;

	line = ft_strdup_bis("", gc);
	data->i = 0;
	while (line != NULL && data->flag == 0)
	{
		data->i = 0;
		if (ft_strncmp(line, "", 1) != 0)
			free(line);
		line = get_next_line(fd);
		ft_lose_space(line, &data->i);
		r = ft_check_if_texture(&data->i, line);
		// printf("r = %d\n", r);
		if (r == 9)
			return (free(line), (1));
		if (r == 0)
		{
			printf("Error: Missing texture or color\n");
			return (free(line), (1));
		}
		if (r == 8)
			data->flag = 1;
		ft_lose_space(line, &data->i);
		if (r != 7 && ft_process_data(r, line, data, gc) == 1)
			return (free(line), (1));
		// free(line);
	}
	// printf("ea = %s\n", data->ea);
	// printf("no = %s\n", data->no);
	// printf("so = %s\n", data->so);
	// printf("we = %s\n", data->we);
	if (ft_check_walls(data, gc) == 1)
		return (free(line), (1));
	free(line);
	return (0);
}

int	ft_parsing(char **argv, t_data *data, t_gc *gc)
{
	int	fd;

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
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error while opening file");
		return (1);
	}
	if (ft_get_data(fd, data, gc) == 1)
		return (close(fd), (1));
	close(fd);
	return (0);
}
