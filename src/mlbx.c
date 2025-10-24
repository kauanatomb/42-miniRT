/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	display(t_rt *rt)
{
	// launch_cam_rays(rt);
	mlx_put_image_to_window(rt->mlbx->mlx, rt->mlbx->mlx_win,
		rt->mlbx->img.img, 0, 0);
	return (0);
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
	if (keycode == 65307)
		destroy(rt);
	return (0);
}

void	make_window(t_rt *rt)
{
	t_mlbx	*mlbx;

	mlbx = malloc(sizeof(t_mlbx));
	rt->mlbx = mlbx;
	rt->mlbx->mlx = mlx_init();
	rt->mlbx->mlx_win = mlx_new_window(mlbx->mlx, rt->win_w,
			rt->win_h, "MiniRT");
	rt->mlbx->img.img = mlx_new_image(mlbx->mlx, rt->win_h, rt->win_h);
	rt->mlbx->img.addr = mlx_get_data_addr(mlbx->img.img,
			&mlbx->img.bits_p_pixel, &mlbx->img.size_line, &mlbx->img.endian);
	display(rt);
	mlx_hook(mlbx->mlx_win, 17, 0, destroy, rt);
	mlx_key_hook(mlbx->mlx_win, key_function, rt);
	mlx_loop(mlbx->mlx);
}
