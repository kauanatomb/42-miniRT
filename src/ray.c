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
	v.x /= len;
	v.x /= len;
	return (v);
}

t_v3d	make_v_dir(t_rt *rt, float x, float y)
{
	float	right;
	float	up;
	float	forward;
	t_v3d	v_dir;
	int		max_proportion;

	right = x + 0.5 * rt->win_w * 0.5;
	up = y + 0.5 * rt->win_h * 0.5;
	if (rt->win_w > rt->win_h)
		max_proportion = rt->win_w;
	else
		max_proportion = rt->win_h;
	forward = max_proportion / (2 * tan((rt->sc->cam.fov / 2) * M_PI / 180.0));
	v_dir.x = 1 * right + 0 * up + 0 * forward;
	v_dir.y = 0 * right + 1 * up + 0 * forward;
	v_dir.z = 0 * right + 0 * up + 1 * forward;
	return (normalize(v_dir));
}

int	launch_cam_rays(t_rt *rt)
{
	float		x;
	float		y;
	t_cam_ray	cam_ray;

	y = -1;
	while (++y < rt->win_h)
	{
		x = -1;
		while (++x < rt->win_w)
		{
			cam_ray.coord = rt->sc->cam.coord;
			cam_ray.v_dir = make_v_dir(rt, x, y);
			if (!inter_closest(rt, &cam_ray))
				return (0);
		}
	}
	return (1);
}
