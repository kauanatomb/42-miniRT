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

void	translate(t_v3d *pos, t_v3d delta)
{
	*pos = add(*pos, delta);
}

void	cam_yaw(t_camera *cam, float angle)
{
	cam->forward = rotate_axis(cam->forward, (t_v3d){0, 1, 0}, angle);
	cam->right = rotate_axis(cam->right, (t_v3d){0, 1, 0}, angle);
	cam->up = rotate_axis(cam->up, (t_v3d){0, 1, 0}, angle);
}

void	cam_pitch(t_camera *cam, float angle)
{
	cam->forward = rotate_axis(cam->forward, cam->right, angle);
	cam->up = rotate_axis(cam->up, cam->right, angle);
}

void	handle_light_movement(int keycode, t_light *l, t_camera *cam)
{
	if (keycode == L_FORWARD)
		translate(&l->coord, sc_mult(cam->forward, 5.0));
	else if (keycode == L_BACKWARD)
		translate(&l->coord, sc_mult(cam->forward, -5.0));
	else if (keycode == L_RIGHT)
		translate(&l->coord, sc_mult(cam->right, 5.0));
	else if (keycode == L_LEFT)
		translate(&l->coord, sc_mult(cam->right, -5.0));
	else if (keycode == L_UP)
		translate(&l->coord, sc_mult(cam->up, 5.0));
	else if (keycode == L_DOWN)
		translate(&l->coord, sc_mult(cam->up, -5.0));
}

void	handle_cam_moviment(int keycode, t_camera *cam)
{
	if (keycode == W)
		translate(&cam->coord, sc_mult(cam->forward, 5));
	else if (keycode == S)
		translate(&cam->coord, sc_mult(cam->forward, -5));
	else if (keycode == A)
		translate(&cam->coord, sc_mult(cam->right, -5));
	else if (keycode == D)
		translate(&cam->coord, sc_mult(cam->right, 5));
	else if (keycode == Q)
		translate(&cam->coord, sc_mult(cam->up, 5));
	else if (keycode == E)
		translate(&cam->coord, sc_mult(cam->up, -5));
	else if (keycode == UP_ARROW)
		cam_pitch(cam, -5 * M_PI / 180);
	else if (keycode == DOWN_ARROW)
		cam_pitch(cam, 5 * M_PI / 180);
	else if (keycode == LEFT_ARROW)
		cam_yaw(cam, -5 * M_PI / 180);
	else if (keycode == RIGHT_ARROW)
		cam_yaw(cam, 5 * M_PI / 180);
}
