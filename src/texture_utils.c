/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:46:45 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/20 18:08:27 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_rgb(int color, double shade)
{
	unsigned char r = ((color >> 16) & 0xFF) * shade;
	unsigned char g = ((color >> 8) & 0xFF) * shade;
	unsigned char b = (color & 0xFF) * shade;
	return (color = (r << 16) | (g << 8) | b);
}

void	ft_choose_texture(t_mlx_data *pdata)
{
	if (pdata->dda.side == 0)
	{
		if (pdata->dda.rayDirX > 0)
			pdata->current_txt = &pdata->txt_west;
		else
			pdata->current_txt = &pdata->txt_east;
	}
	else
	{
		if (pdata->dda.rayDirY > 0)
			pdata->current_txt = &pdata->txt_north;
		else
			pdata->current_txt = &pdata->txt_south;
	}
}

// static int	ft_rgb_convert(int rgb[3])
static int	ft_rgb_convert(int r, int g, int b)
{
	// if (!rgb)
	// 	return (0); // ou gérer l'erreur autrement
	return ((r << 16) | (g << 8) | b);
}


void	ft_floorceil(t_mlx_data *pdata, t_data *data_erika)
{
	int	y_fill;
	int	x_fill;
	// int	floor_color;
	// int	ceil_color;
	// int		rgb[3]= {30, 30, 30};

	// printf("1 = %d, 2 = %d, 3 = %d\n", data_erika->ceiling[0], data_erika->ceiling[1], data_erika->ceiling[2]);
	// printf("%d\n", pdata->rr);
	// printf("%d\n", ft_rgb_convert(rgb));
	(void)data_erika;////////////////////////////////////////////////////
	y_fill = 0;
	while (y_fill < HEIGHT / 2)
	{
		x_fill = 0;
		while (x_fill < WIDTH)
			ft_pixput(pdata, x_fill++, y_fill, ft_rgb_convert(pdata->crr, pdata->cgg, pdata->cbb));//plafond ?
			// ft_pixput(pdata, x_fill++, y_fill, ft_rgb_convert(data_erika->ceiling[0], data_erika->ceiling[1], data_erika->ceiling[1]));//plafond ?
			// ft_pixput(pdata, x_fill++, y_fill, 0xAAAAAA);//plafond ?
		y_fill++;
	}
	while (y_fill < HEIGHT)
	{
		x_fill = 0;
		while (x_fill < WIDTH)
			// ft_pixput(pdata, x_fill++, y_fill, 0x333333);
			ft_pixput(pdata, x_fill++, y_fill, ft_rgb_convert(pdata->frr, pdata->fgg, pdata->fbb));
		y_fill++;
	}
}
