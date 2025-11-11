/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/11/11 14:45:15 by falatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3d	normalize(t_v3d v)
{
	float	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0)
		return (v);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return (v);
}

t_v3d	make_v_dir(t_rt *rt, float x, float y)
{
	t_camera	*cam;
	t_v3d		ray_dir;
	float		fov_rad;
	float		px;
	float		py;

	cam = &rt->sc->cam;
	fov_rad = cam->fov * M_PI / 180.0;
	px = (2.0 * (x + 0.5) / rt->win_w - 1.0) * \
	tan(fov_rad / 2.0) * ((float)rt->win_w / (float)rt->win_h);
	py = (1.0 - 2.0 * (y + 0.5) / rt->win_h) * tan(fov_rad / 2.0);
	ray_dir = add(
			add(sc_mult(cam->right, px), sc_mult(cam->up, py)),
			cam->forward
			);
	return (normalize(ray_dir));
}

void	init_camera(t_camera *cam)
{
	t_v3d	up_guide;

	up_guide = (t_v3d){0, 1, 0};
	cam->forward = normalize(cam->ori);
	if (fabs(cam->forward.x) == 0 && fabs(cam->forward.z) == 0)
		up_guide = (t_v3d){0, 0, 1};
	cam->right = normalize(cross(up_guide, cam->forward));
	cam->up = cross(cam->forward, cam->right);
}

t_v3d	rotate_y(t_v3d v, float angle)
{
	t_v3d	new;

	new.x = v.x * cos(angle) + v.z * sin(angle);
	new.y = v.y;
	new.z = -v.x * sin(angle) + v.z * cos(angle);
	return (normalize(new));
}

int	launch_cam_rays(t_rt *rt)
{
	float		x;
	float		y;
	t_cam_ray	cam_ray;
	t_color		final_color;

	y = -1;
	while (++y < rt->win_h)
	{
		x = -1;
		while (++x < rt->win_w)
		{
			cam_ray.coord = rt->sc->cam.coord;
			cam_ray.v_dir = make_v_dir(rt, x, y);
			if (!inter_closest(rt, &cam_ray))
				final_color = (t_color){0, 0, 0};
			else
				final_color = compute_light(rt, cam_ray.inter);
			my_mlx_pixel_put(rt->mlbx->img, x, y, rgb_to_int(final_color));
		}
	}
	return (1);
}
