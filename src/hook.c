/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:05:27 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/20 16:31:49 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


double	ft_fb(t_mlx_data *pdata, int which, int key)
{
	if (key == XK_w)
	{
		if (!which)
			return (pdata->posX + pdata->dirX * pdata->moveSpeed);
		return (pdata->posY + pdata->dirY * pdata->moveSpeed);
	}
	if (key == XK_s)
	{
		if (!which)
			return (pdata->posX - pdata->dirX * pdata->moveSpeed);
		return (pdata->posY - pdata->dirY * pdata->moveSpeed);
	}
	return (0.0);
}

void	ft_fbmove(int key, t_mlx_data *pdata)
{
	if (key == XK_w)
	{
		if (pdata->map[(int)(pdata->posY)][(int)ft_fb(pdata, 0, XK_w)] == '0')
			pdata->posX += pdata->dirX * pdata->moveSpeed;
		if (pdata->map[(int)ft_fb(pdata, 1, XK_w)][(int)(pdata->posX)] == '0')
			pdata->posY += pdata->dirY * pdata->moveSpeed;
	}
	if (key == XK_s)
	{
		if (pdata->map[(int)(pdata->posY)][(int)ft_fb(pdata, 0, XK_s)] == '0')
			pdata->posX -= pdata->dirX * pdata->moveSpeed;
		if (pdata->map[(int)ft_fb(pdata, 1, XK_s)][(int)(pdata->posX)] == '0')
			pdata->posY -= pdata->dirY * pdata->moveSpeed;
	}
}

double	ft_lat(t_mlx_data *pdata, int which, int key)
{
	if (key == XK_d)
	{
		if (!which)
			return (pdata->posX + pdata->planeX * pdata->moveSpeed);
		return (pdata->posY + pdata->planeY * pdata->moveSpeed);
	}
	if (key == XK_a)
	{
		if (!which)
			return (pdata->posX - pdata->planeX * pdata->moveSpeed);
		return (pdata->posY - pdata->planeY * pdata->moveSpeed);
	}
	return (0.0);
}

void	ft_latmove(int key, t_mlx_data *pdata)
{
	if (key == XK_d)
	{
		if (pdata->map[(int)(pdata->posY)][(int)ft_lat(pdata, 0, XK_d)] == '0')
			pdata->posX += pdata->planeX * pdata->moveSpeed;
		if (pdata->map[(int)ft_lat(pdata, 1, XK_d)][(int)(pdata->posX)] == '0')
			pdata->posY += pdata->planeY * pdata->moveSpeed;
	}
	if (key == XK_a)
	{
		if (pdata->map[(int)(pdata->posY)][(int)ft_lat(pdata, 0, XK_a)] == '0')
			pdata->posX -= pdata->planeX * pdata->moveSpeed;
		if (pdata->map[(int)ft_lat(pdata, 1, XK_a)][(int)(pdata->posX)] == '0')
			pdata->posY -= pdata->planeY * pdata->moveSpeed;
	}
}

int ft_loophook(t_mlx_data *data, t_data *data_erika)
{
	if (data->move_forward)
		ft_fbmove(XK_w, data);
	if (data->move_backward)
		ft_fbmove(XK_s, data);
	if (data->move_left)
		ft_latmove(XK_a, data);
	if (data->move_right)
		ft_latmove(XK_d, data);
	if (data->rotate_left)
		ft_turnview(XK_Left, data);
	if (data->rotate_right)
		ft_turnview(XK_Right, data);
	if (data->exit_requested)
	{
		ft_stop(data); // ou data->gc si tu l’as stocké
		exit(0);
	}
	ft_display(data, data_erika, NULL); // Mise à jour de l'affichage à chaque frame
	return (0);
}
