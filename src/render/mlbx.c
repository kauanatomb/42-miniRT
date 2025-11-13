/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlbx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/11/07 14:26:12 by falatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	display(t_rt *rt)
{
	init_camera(&rt->sc->cam);
	if (!launch_cam_rays(rt))
		return (0);
	mlx_put_image_to_window(rt->mlbx->mlx, rt->mlbx->mlx_win,
		rt->mlbx->img.img, 0, 0);
	return (1);
}

int	destroy(t_rt *rt)
{
	mlx_destroy_image(rt->mlbx->mlx, rt->mlbx->img.img);
	mlx_destroy_window(rt->mlbx->mlx, rt->mlbx->mlx_win);
	mlx_destroy_display(rt->mlbx->mlx);
	clean_rt_scene(rt);
	exit(0);
	return (0);
}

int	key_function(const int keycode, t_rt *rt)
{
	t_camera	*cam;

	cam = &rt->sc->cam;
	if (keycode == ESC)
		destroy(rt);
	else if (keycode == W)
		cam->coord = add(cam->coord, sc_mult(cam->forward, 5));
	else if (keycode == S)
		cam->coord = add(cam->coord, sc_mult(cam->forward, -5));
	else if (keycode == A)
		cam->coord = add(cam->coord, sc_mult(cam->right, -5));
	else if (keycode == D)
		cam->coord = add(cam->coord, sc_mult(cam->right, 5));
	else if (keycode == Q)
		cam->coord = add(cam->coord, sc_mult(cam->up, 5));
	else if (keycode == E)
		cam->coord = add(cam->coord, sc_mult(cam->up, -5));
	else if (keycode == LEFT_ARROW)
		cam->ori = rotate_y(cam->ori, -5 * M_PI / 180);
	else if (keycode == RIGHT_ARROW)
		cam->ori = rotate_y(cam->ori, 5 * M_PI / 180);
	display(rt);
	return (0);
}

int	make_window(t_rt *rt)
{
	t_mlbx	*mlbx;

	mlbx = malloc(sizeof(t_mlbx));
	if (!mlbx)
		return (print_error("Malloc error mlbx"));
	rt->mlbx = mlbx;
	rt->mlbx->mlx = mlx_init();
	rt->mlbx->mlx_win = mlx_new_window(mlbx->mlx, rt->win_w,
			rt->win_h, "MiniRT");
	rt->mlbx->img.img = mlx_new_image(mlbx->mlx, rt->win_w, rt->win_h);
	rt->mlbx->img.addr = mlx_get_data_addr(mlbx->img.img,
			&mlbx->img.bits_p_pixel, &mlbx->img.size_line, &mlbx->img.endian);
	if (!display(rt))
		return (0);
	mlx_hook(mlbx->mlx_win, 17, 0, destroy, rt);
	mlx_key_hook(mlbx->mlx_win, key_function, rt);
	mlx_loop(mlbx->mlx);
	return (1);
}

void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = img.addr + (y * img.size_line
				+ x * (img.bits_p_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
