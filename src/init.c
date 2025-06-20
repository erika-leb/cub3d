/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/20 16:24:40 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// pdata->dirX = -1;//Regard a gauche (arbitraire) sur le plan [-1, 1] OU L'INVERSE ?? CHELOU
// pdata->dirY = 0;//regard ni en haut ni en bas mais au milieu
//  sur le plan [1, -1] pdata->planeX = 0;//permet une ligne perpendiculaire
// pdata->planeY = 0.66;//et ps 1 pour que ce soit un peu plus realiste
// ...
//(A TESTER)
// pdata->error = 0;//Initialisation terminée,
//  pas de message d'erreur dans ft_stop

//Present dans la libft : OUI
//Useful si je veux utiliser les dummies de_wnd etc en cas de prb ou en fin de
//code.
//En effet en mettant des 0's partout on peut faire des if (!pdata->img_ptr)...

static void	ft_bzero(void *pointer, size_t times)
{
	unsigned char	*buffer;
	unsigned int	i;

	i = 0;
	buffer = (unsigned char *)pointer;
	while (times--)
	{
		buffer[i] = 0;
		i++;
	}
}

static void ft_initdir(t_mlx_data *data, char direction)
{
	//'N'
	data->dirX = 0;
	data->dirY = -1;
	data->planeX = 0.66;
	data->planeY = 0;
	if (direction == 'S') // Sud
	{
		data->dirY = 1;
		data->planeX = -0.66;
	}
	else if (direction == 'E') // Est
	{
		data->dirX = 1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	else if (direction == 'W') // Ouest
	{
		data->dirX = -1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = -0.66;
	}
}


// static void	ft_initplayer(t_mlx_data *pdata, t_data *data_erika, char **map) //ici
static void	ft_initplayer(t_mlx_data *pdata, t_data *data_erika)
{
	// (void)data_erika;
	pdata->map = data_erika->map; //ici
	// pdata->map = NULL;
	pdata->posX = data_erika->pos_x;//12
	pdata->posY = data_erika->pos_y;//10
	pdata->dirX = 0;
	pdata->dirY = -1;
	pdata->planeX = 0.66;
	pdata->planeY = 0;
	ft_initdir(pdata, data_erika->pos);
	pdata->moveSpeed = 0.0125;
	pdata->rotSpeed = 0.00625;
	pdata->move_forward = 0;
	pdata->move_backward = 0;
	pdata->rotate_left = 0;
	pdata->rotate_right = 0;
	pdata->move_left = 0;
	pdata->move_right = 0;
	pdata->error = 0;
	pdata->smap = 0;
	pdata->exit_requested = 0;
	// perror("it's");
}

// void	ft_init(t_mlx_data *pdata, t_data *data_erika, t_gc *gc, char **map) //ici
void	ft_init(t_mlx_data *pdata, t_data *data_erika, t_gc *gc)
{
	ft_bzero(pdata, sizeof(t_mlx_data));
	pdata->error = 1;
	pdata->connect = mlx_init();
	if (!pdata->connect)
		ft_stop(pdata);
	pdata->error = 2;
	pdata->win_ptr = mlx_new_window(pdata->connect, WIDTH, HEIGHT, "Cub3d");
	if (!pdata->win_ptr)
		ft_stop(pdata);
	pdata->error = 3;
	pdata->img_ptr = mlx_new_image(pdata->connect, WIDTH, HEIGHT);
	if (!pdata->img_ptr)
		ft_stop(pdata);
	pdata->error = 4;
	pdata->img_pixptr = mlx_get_data_addr(pdata->img_ptr, &pdata->bpp,
			&pdata->len, &pdata->endian);
	//Pour chaque texture N S E O on fait la même chose :
	pdata->txt_north.data = mlx_xpm_file_to_image(pdata->connect, data_erika->no, &pdata->txt_north.width, &pdata->txt_north.height);//"./textures/wall_1.xpm"
	pdata->txt_south.data = mlx_xpm_file_to_image(pdata->connect, data_erika->so, &pdata->txt_south.width, &pdata->txt_south.height);//"./textures/wall_2.xpm"
	pdata->txt_east.data  = mlx_xpm_file_to_image(pdata->connect, data_erika->ea, &pdata->txt_east.width, &pdata->txt_east.height);//"./textures/wall_3.xpm"
	pdata->txt_west.data  = mlx_xpm_file_to_image(pdata->connect, data_erika->we, &pdata->txt_west.width, &pdata->txt_west.height);//"./textures/wall_4.xpm"
	if (!pdata->txt_north.data || !pdata->txt_south.data || !pdata->txt_east.data || !pdata->txt_west.data)
		ft_stop(pdata);
	pdata->txt_north.addr = mlx_get_data_addr(pdata->txt_north.data, &pdata->txt_north.bpp, &pdata->txt_north.size_line, &pdata->txt_north.endian);
	pdata->txt_south.addr = mlx_get_data_addr(pdata->txt_south.data, &pdata->txt_south.bpp, &pdata->txt_south.size_line, &pdata->txt_south.endian);
	pdata->txt_east.addr = mlx_get_data_addr(pdata->txt_east.data, &pdata->txt_east.bpp, &pdata->txt_east.size_line, &pdata->txt_east.endian);
	pdata->txt_west.addr = mlx_get_data_addr(pdata->txt_west.data, &pdata->txt_west.bpp, &pdata->txt_west.size_line, &pdata->txt_west.endian);
	// ft_initplayer(pdata, data_erika, map); //ici
	ft_initplayer(pdata, data_erika); //ici
	pdata->gc = gc;
}

