/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/02 14:04:21 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_check_extention(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i < 5)
		return (1);
	if (s[i - 1] != 'b')
		return (1);
	if (s[i - 2] != 'u')
		return (1);
	if (s[i - 3] != 'c')
		return (1);
	if (s[i - 4] != '.')
		return (1);
	return (0);
}

void	ft_lose_space(char *s, int *i)
{
	// perror("text 1");
	while (s && s[*i] && ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == 32))
		(*i) = (*i) + 1;
	// perror("text 2");
}

int ft_check_if_texture(int *i, char *line)
{
	int	r;

	r = 0;
	// printf("ligne = %sj\n", line);
	// printf("i = %d\n", i);
	// printf("line[i] = %c\n", line[i]);
	if (ft_strncmp(line + (*i), "NO ", 3) == 0)
	{
		// perror("ICI");
		r = 1;
	}
	if (ft_strncmp(line + (*i), "SO ", 3) == 0)
		r = 2;
	if (ft_strncmp(line + (*i), "WE ", 3) == 0)
		r = 3;
	if (ft_strncmp(line + (*i), "EA ", 3)== 0)
		r = 4;
	if (ft_strncmp(line + (*i), "C ", 2) == 0)
		r = 5;
	if (ft_strncmp(line + (*i), "F ", 2) == 0)
		r = 6;
	if (ft_strncmp(line + (*i), "\0", 1) == 0)
	{
		// perror("la");
		r = 7;
	}
	return (r);
}

char	*ft_get_file(char *line, t_data *data, t_gc *gc)
{
	char	*s;
	int		size;
	int		t;

	size = data->i;
	while (line[data->i] != ' ')
		(data->i)++;
	ft_lose_space(line, &data->i);
	t = 0;
	while (line[data->i + t] && (line[data->i + t] != '\n' || line[data->i + t] != '\0' || line[data->i + t] == ' '))
		t++;
	s = gc_malloc(sizeof(char) * (t + 1), gc);
	t = 0;
	while (line[data->i] && (line[data->i] != '\n' || line[data->i] != '\0' || line[data->i] == ' '))
	{
		s[t] = line[data->i];
		(data->i)++;
		t++;
	}
	s[t] = '\0';
	return (s);
}


int ft_process_data(int r, char *line, t_data *data, t_gc *gc)
{
	if (r == 1)
	{
		if (data->no != NULL)
		{
			printf("Error: Duplicated texture or color\n");
			return (1);
		}
		data->no = ft_get_file(line, data, gc);
		if (data->no == NULL) //si quelque chose ne va pas sur la ligne
		{
			printf("Error: Wrong texture or color\n");
			return (1);
		}
		printf("res = %s\n", data->no);
	}
	return (0);
}

int	ft_get_data(int fd, t_data *data, t_gc *gc)
{
	char	*line;
	int		r;

	line = ft_strdup("");
	data->i = 0;
	while (line != NULL && data->t == 0)
	{
		data->i = 0;
		// printf("bef = %d\n", i);
		line = get_next_line(fd);
		ft_lose_space(line, &data->i);
		r = ft_check_if_texture(&data->i, line);
		if (r == 0)
		{
			printf("Error: Missing texture or color\n");
			return (1);
		}
		ft_lose_space(line, &data->i);
		if (r != 7 && ft_process_data(r, line, data, gc) == 1)
			return (1); //message erreur ???
		// perror("passe");
		// printf("i = %d, letter = %c\n", i, line[i]);
	}
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
		write(2,"Error: No .cub file found\n", 27);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error while opening file");
		return (1);
	}
	if (ft_get_data(fd, data, gc) == 1)
	{
		//write(2,"Error: Invalid file\n", 21);
		return (1);
	}
	close(fd);
	return (0);
}

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
	data->t = 0;
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
