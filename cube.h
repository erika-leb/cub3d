/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 17:48:09 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "gc/gc.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_data
{
	char	*f;
	char	*c;
	char	*so;
	char	*ea;
	char	*no;
	char	*we;
	int		*floor;
	int		*ceiling;
	char	**map;
	int		i;
	int		flag;
	char	*s1;
	char	*stash;
}	t_data;

//main.c
int		ft_parsing(char **argv, t_data *data, t_gc *gc);

//parsing.c
int		ft_parsing(char **argv, t_data *data, t_gc *gc);

//parsing_get_texture.c
int		ft_check_if_texture(int *i, char *line);
int		ft_process_data(int r, char *line, t_data *data, t_gc *gc);

//parsing_check_texture.c
int		ft_check_walls(t_data *data, t_gc *gc);

//parsing_check_color.c
int		ft_check_color(t_data *data, t_gc *gc);

//parsing_extention.c
int		ft_xpm_extention(char *s);
int		ft_check_extention(char *s);

//get_next_line.c
char	*get_next_line(int fd, t_data *data);

//get_next_line_utils.c
int		ft_strlen(char *s);
int		ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
void	*ft_calloc(size_t count, size_t size);

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup_bis(char *s, t_gc *gc);
void	ft_lose_space(char *s, int *i);
int		ft_is_space(char c);

#endif
