/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	top_cap_cy(t_cam_ray *ray, t_cylinder *cy, float *best,
	t_v3d *best_normal)
{
	float		t;
	t_v3d		center;
	t_v3d		hit;
	t_v3d		cp;
	float		dist2;

	center = add(cy->coord, sc_mult(cy->ori, cy->h));
	if (fabs(dot_product(ray->v_dir, cy->ori)) > 1e-6)
	{
		t = dot_product(sub(center, ray->coord), cy->ori)
			/ dot_product(ray->v_dir, cy->ori);
		if (t > 0)
		{
			hit = add(ray->coord, sc_mult(ray->v_dir, t));
			cp = sub(hit, center);
			dist2 = dot_product(cp, cp);
			if (dist2 <= cy->r * cy->r && t < *best)
			{
				*best = t;
				*best_normal = cy->ori;
			}
		}
	}
}

void	bottom_cap_cy(t_cam_ray *ray, t_cylinder *cy, float *best,
	t_v3d *best_normal)
{
	float		t;
	t_v3d		center;
	t_v3d		hit;
	t_v3d		cp;
	float		dist2;

	center = cy->coord;
	if (fabs(dot_product(ray->v_dir, cy->ori)) > 1e-6)
	{
		t = dot_product(sub(center, ray->coord), cy->ori)
			/ dot_product(ray->v_dir, cy->ori);
		if (t > 0)
		{
			hit = add(ray->coord, sc_mult(ray->v_dir, t));
			cp = sub(hit, center);
			dist2 = dot_product(cp, cp);
			if (dist2 <= cy->r * cy->r && t < *best)
			{
				*best = t;
				*best_normal = sc_mult(cy->ori, -1);
			}
		}
	}
}

int	cap_cy(t_cam_ray *ray, t_cylinder *cy, t_inter *tmp)
{
	float		best;
	t_v3d		best_normal;

	best = INFINITY;
	bottom_cap_cy(ray, cy, &best, &best_normal);
	top_cap_cy(ray, cy, &best, &best_normal);
	if (best < tmp->dist)
	{
		tmp->dist = best;
		tmp->normal = best_normal;
		return (1);
	}
	return (0);
}
