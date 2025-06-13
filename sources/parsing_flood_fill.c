/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/13 16:43:01 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//penser au cas avec une seule ligne ou une seule colonne a tester

// void	ft_copy_map(t_data *data, t_gc *gc)
// {
// 	int	k;
// 	int	i;

// 	k = 0;
// 	data->m = gc_malloc(sizeof(char *) * (data->lg + 1), gc);
// 	while (k < data->lg)
// 	{
// 		i = 0;
// 		data->m[k] = gc_malloc(sizeof(char) * (data->cl + 1), gc);
// 		while (data->map[k][i] && data->map[k][i] != '\n')
// 		{
// 			if (ft_is_space(data->map[k][i]) == 1)
// 				data->m[k][i] = '1';
// 			else
// 				data->m[k][i] = data->map[k][i];
// 			i++;
// 		}
// 		data->m[k][i] = '\0';
// 		k++;
// 	}
//     data->m[k] = NULL;
//     k = 0;
// 	perror("deuxieme");
//     while (data->m[k])
//     {
//         printf("%s\n", data->m[k]);
//         k++;
//     }
// }

// int	ft_up_down(t_data *data, int l)
// {
// 	int	c;

// 	c = 0;
// 	if (l == 0 || l == data->lg - 1) //premiere et derniere ligne
// 	{
// 		while (data->m[l][c])
// 		{
// 			if (data->m[l][c] != '1')
// 			{
// 				printf("l = %d, c = %d\n", l, c);
// 				return (1);
// 			}
// 			c++;
// 		}
// 	}
// 	return (0);
// }

// int	ft_is_closed(t_data *data)
// {
// 	int	c;
// 	int	l;

// 	l = -1;
// 	while (++l < data->lg)
// 	{
// 		c = 0;
// 		if (ft_up_down(data, l) == 1)
// 		{
// 			// perror("ici");
// 			return (1);
// 		}
// 		// if (l == 0 || l == data->lg - 1) //premiere et derniere ligne
// 		// {
// 		// 	while (data->map[l][c])
// 		// 	{
// 		// 		if (data->map[l][c] == '0')
// 		// 			return (1);
// 		// 		c++;
// 		// 	}
// 		// }
// 		while (ft_is_space(data->m[l][c]) == 1)
// 			c++;
// 		if (data->m[l][c] != '1')
// 		{
// 			// perror("la");
// 			return (1);
// 		}
// 		c = data->cl - 1;
// 		while (ft_is_space(data->m[l][c]) == 1)
// 			c--;
// 		if (data->m[l][c] != '1')
// 		{
// 			// perror("encore");
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int	ft_check_player(t_data *data, int *f, int c, int l)
{
	if ((data->map[l][c] == 'S' || data->map[l][c] == 'E' || data->map[l][c] == 'W'
		|| data->map[l][c] == 'N') && (*f) == 1)
	{
		printf("Error\nMultiple players\n");
		return (1);
	}
	if (data->map[l][c] == 'S' || data->map[l][c] == 'E' || data->map[l][c] == 'W'
		|| data->map[l][c] == 'N')
	{
		(*f) = 1;
		// data->pos_c = c;
		// data->pos_l = l;
		data->pos = data->map[l][c];
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
			if (ft_check_player(data, &f, c, l) == 1)
				return (1);
			// if ((data->map[l][c] == 'S' || data->map[l][c] == 'E' || data->map[l][c] == 'W'
			// 		|| data->map[l][c] == 'N') && f == 1)
			// {
			// 	printf("Error: multiple players\n");
			// 	return (1);
			// }
			// if (data->map[l][c] == 'S' || data->map[l][c] == 'E' || data->map[l][c] == 'W'
			// 		|| data->map[l][c] == 'N')
			// {
			// 	f = 1;
			// 	data->pos_c = c;
			// 	data->pos_l = l;
			// 	data->pos = data->map[l][c];
			// }
			// printf("or if c = %d\n", c);
			c++;
		}
		l++;
	}
	if (f == 0)
	{
		printf("Error\nNo player\n");
		return (1);
	}
	return (0);
}
int	ft_is_o(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
		return (1);
	return (0);
}

int	ft_flood(t_data *data, int l, int c)
{
	//voir les extremites
	if (!(data->map[l][c + 1] && (data->map[l][c + 1] == '1' || ft_is_o(data->map[l][c + 1]) == 1))) // droite
		return (1);
	if (!(c != 0 && (data->map[l][c - 1] == '1' || ft_is_o(data->map[l][c - 1]) == 1))) // gauche
		return (1);
	if (!(l != 0 && (data->map[l - 1][c] == '1' || ft_is_o(data->map[l - 1][c]) == 1))) // en haut
		return (1);
	if (!(data->map[l + 1] && (data->map[l + 1][c] == '1' || ft_is_o(data->map[l + 1][c]) == 1))) // bas
		return (1);
	return (0);
}

int	ft_is_map_valid(t_data *data)
{
	int	l;
	int	c;

	l = 0;
	while (l < data->lg)
	{
		c = 0;
		while (c < data->cl)
		{
			if (ft_is_o(data->map[l][c]) == 1)
			{
				if (ft_flood(data, l, c) == 1)
				{
					printf("Error\nInvalid map\n");
					return (1);
				}
			}
			c++;
		}
		l++;
	}
	return (0);
}

int	ft_flood_fill(t_data *data, t_gc *gc)
{
	// ft_copy_map(data, gc);
	// if (ft_is_closed(data) == 1)
	// {
	// 	printf("Error: map not closed\n");
	// 	return (1);
	// }

	//verifier qu il y a une map
	(void) gc;
	// printf("map =%s\n", data->map[0]);
	if (!data->map[0])
	{
		printf("Error\nNo map\n");
		return (1);
	}
	if (ft_is_map_valid(data) == 1)
		return (1);
	if (ft_get_pos(data) == 1)
		return (1);
	// printf("pos = %c, l = %d, c = %d\n", data->pos, data->pos_l, data->pos_c);
	return (0);
}
