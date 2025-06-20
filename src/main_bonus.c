/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/20 16:32:21 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//Pour le bonus : VERIFIER QUE C'EST BIEN CE QU'ON ATTEND DE NOUS
static int	mouse_move_hook(int x, int y, t_data *data_erika, t_mlx_data *pdata)
{
	static int	last_x = -1;
	double		rotSpeed;
	(void)y;

	if (last_x == -1)
		last_x = x;

	int delta_x = x - last_x;
	last_x = x;

	rotSpeed = 0.003 * delta_x; // Sensibilité

	// ✅ Rotation avec le bon signe
	double oldDirX = pdata->dirX;
	pdata->dirX = pdata->dirX * cos(rotSpeed) - pdata->dirY * sin(rotSpeed);
	pdata->dirY = oldDirX * sin(rotSpeed) + pdata->dirY * cos(rotSpeed);

	double oldPlaneX = pdata->planeX;
	pdata->planeX = pdata->planeX * cos(rotSpeed) - pdata->planeY * sin(rotSpeed);
	pdata->planeY = oldPlaneX * sin(rotSpeed) + pdata->planeY * cos(rotSpeed);

	ft_display(pdata, data_erika, draw_minimap); // Rafraîchir l'affichage

	return (0);
}





int ft_loophookbonus(t_mlx_data *data, t_data *data_erika)
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
	ft_display(data, data_erika, draw_minimap); // Mise à jour de l'affichage à chaque frame
	return (0);
}


static void draw_square(t_mlx_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
    {
		j = -1;
		while (++j < size)
            ft_pixput(data, x + j, y + i, color);
    }
}

//Est / Ouest inverse dans le jeu donc ca vient pas de la minimap
static void draw_minimap(t_mlx_data *data)
{
	int mapX, mapY, color;

	double cell_w = (double)MINIMAP_WIDTH / MAPWIDTH;
	double cell_h = (double)MINIMAP_HEIGHT / MAPHEIGHT;

	int offset_x = WIDTH - MINIMAP_WIDTH - 10;
	int offset_y = 10;

	// --- Dessin des cases de la carte ---
	for (mapY = 0; mapY < MAPHEIGHT; mapY++)
	{
		for (mapX = 0; mapX < MAPWIDTH; mapX++)
		{
			color = (worldMap[mapY][mapX] == '0') ? 0x000000 : 0xFFFFFF;

			// ✅ plus d’inversion : mapX * cell_w
			draw_square(data,
				offset_x + (int)(mapX * cell_w),
				offset_y + (int)(mapY * cell_h),
				(int)cell_w,
				color);
		}
	}

	// --- Dessin du joueur ---
	double player_map_x = data->posX * cell_w;
	double player_map_y = data->posY * cell_h;

	int px = offset_x + (int)player_map_x;
	int py = offset_y + (int)player_map_y;
	draw_square(data, px, py, 3, 0x00FF00);

	// --- Ligne de vision (rayon) ---
	double ray_x = data->posX;
	double ray_y = data->posY;
	double step = 0.05;

	while (1)
	{
		int map_check_x = (int)(ray_x + 0.001);
		int map_check_y = (int)(ray_y + 0.001);

		if (map_check_x < 0 || map_check_x >= MAPWIDTH ||
			map_check_y < 0 || map_check_y >= MAPHEIGHT)
			break;
		if (worldMap[map_check_y][map_check_x] > '0')
			break;

		// ✅ plus d’inversion : ray_x * cell_w
		int draw_x = offset_x + (int)(ray_x * cell_w);
		int draw_y = offset_y + (int)(ray_y * cell_h);

		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
			ft_pixput(data, draw_x, draw_y, 0x0000FF);

		ray_x += data->dirX * step;
		ray_y += data->dirY * step;
	}
}


//mettre void plutot que ac av
int	main(int ac, char **av)
{
	(void)ac;
	t_data	*data_erika;
	t_gc	gc;
	t_mlx_data	data;

	gc_init(&gc);
	data_erika = NULL;//useless I guess
	data_erika = ft_init_erika(&gc);
	data_erika->arg = av[1];
	if (ft_parsing(av, data_erika, &gc) == 1)
	{
		gc_cleanup(&gc);
		return (1);
	}

	ft_init(&data, data_erika, &gc);
	ft_display(&data, data_erika, draw_minimap);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, ft_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, ft_keyrelease, &data);
	//SAVOIR L'EXPLIQUER
    mlx_hook(data.win_ptr, 6, 1L<<6, mouse_move_hook, &data); // 6 = MotionNotify 1L<<6 = 64 je crois
	mlx_loop_hook(data.connect, ft_loophookbonus, &data); // appel continu
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data); // Event "fermer la fenêtre"
	mlx_loop(data.connect);



	// perror("la");
	gc_cleanup(&gc);////
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac;
	// (void)av;
	t_data	*data_erika;
	t_gc	gc;
	t_mlx_data	data;

	gc_init(&gc);
	data_erika = NULL;//useless I guess
	data_erika = ft_init_erika(&gc);
	data_erika->arg = av[1];
	if (ft_parsing(av, data_erika, &gc) == 1)
	{
		gc_cleanup(&gc);
		return (1);
	}

	//Croix qui marche pas
	//Frame trop lent
	ft_init(&data, data_erika, &gc);
	// ft_display(&data, NULL);
	ft_display(&data, data_erika, NULL);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, ft_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, ft_keyrelease, &data);
	mlx_loop_hook(data.connect, ft_loophook, &data); // appel continu
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data); // Event "fermer la fenêtre"
	mlx_loop(data.connect);
	// perror("la");
	gc_cleanup(&gc);////
	return (0);
}
