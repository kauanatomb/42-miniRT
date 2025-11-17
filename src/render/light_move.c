/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:07:37 by falatrac          #+#    #+#             */
/*   Updated: 2025/11/14 19:35:03 by falatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	handle_light_keys(int keycode, t_rt *rt)
{
	t_light	*light;
	t_v3d	move;

	light = &rt->sc->light;
	move = (t_v3d){0, 0, 0};
	if (keycode == L_FORWARD)
		move = sc_mult(rt->sc->cam.forward, 5);
	else if (keycode == L_BACKWARD)
		move = sc_mult(rt->sc->cam.forward, -5);
	else if (keycode == L_LEFT)
		move = sc_mult(rt->sc->cam.right, -5);
	else if (keycode == L_RIGHT)
		move = sc_mult(rt->sc->cam.right, 5);
	else if (keycode == L_UP)
		move = sc_mult(rt->sc->cam.up, 5);
	else if (keycode == L_DOWN)
		move = sc_mult(rt->sc->cam.up, -5);
	light->coord = add(light->coord, move);
}

void	handle_cam_translate(int keycode, t_rt *rt)
{
	t_camera	*cam;

	cam = &rt->sc->cam;
	if (keycode == W)
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
}

void	handle_cam_rotate(int keycode, t_rt *rt)
{
	t_camera	*cam;

	cam = &rt->sc->cam;
	if (keycode == LEFT_ARROW)
	{
		cam->ori = rotate_y(cam->ori, -5 * M_PI / 180);
		init_camera(cam);
	}
	else if (keycode == RIGHT_ARROW)
	{
		cam->ori = rotate_y(cam->ori, 5 * M_PI / 180);
		init_camera(cam);
	}
}
