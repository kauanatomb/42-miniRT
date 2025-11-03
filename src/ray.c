/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
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
	float		right;
	float		up;
	float		forward;
	t_v3d		v_dir;
	int			max_proportion;
	t_camera	*cam;

	cam = &rt->sc->cam;
	right = x + 0.5 - rt->win_w * 0.5;
	up = rt->win_h * 0.5 - (y + 0.5);
	if (rt->win_w > rt->win_h)
		max_proportion = rt->win_w;
	else
		max_proportion = rt->win_h;
	forward = max_proportion / (2 * tan((rt->sc->cam.fov / 2) * M_PI / 180.0));
	v_dir.x = right;
	v_dir.y = up;
	v_dir.z = forward;
	v_dir = add(add(sc_mult(cam->right, v_dir.x), sc_mult(cam->up, v_dir.y)), \
	sc_mult(cam->forward, v_dir.z));
	return (normalize(v_dir));
}

void	init_camera(t_camera *cam)
{
	t_v3d	up_guide;

	up_guide = (t_v3d){0, 1, 0};
	cam->forward = normalize(sc_mult(cam->ori, -1));
	cam->right = normalize(cross(up_guide, cam->forward));
	cam->up = cross(cam->forward, cam->right);
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
				final_color = (t_color){200, 200, 200};
			else
				final_color = get_color(cam_ray.inter);
			my_mlx_pixel_put(rt->mlbx->img, x, y, rgb_to_int(final_color));
		}
	}
	return (1);
}
