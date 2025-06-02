/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/02 13:23:17 by ele-borg         ###   ########.fr       */
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
	char	**map;
	int		i;
	int		t;
	char	*s1;
}	t_data;

//main.c
int		ft_parsing(char **argv, t_data *data, t_gc *gc);

//get_next_line.c
char	*get_next_line(int fd);
char	*clean_stash_buffer(char *stash, char *buffer, int *s);
char	*read_and_stock(int fd, char *line, char *buffer, int *n);
char	*ft_strdup(char *s);
int		ft_strlen(char *s);
int		ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_free(char *s);

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
