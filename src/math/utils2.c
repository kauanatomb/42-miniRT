/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/11/13 14:35:41 by falatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	bhaskara(float a, float b, float c)
{
	float	delta;
	float	t0;
	float	t1;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1);
	t0 = (-b - sqrt(delta)) / (2 * a);
	t1 = (-b + sqrt(delta)) / (2 * a);
	if (t0 < 0)
		t0 = t1;
	if (t0 < 0)
		return (-1);
	else if (t1 >= 0 && t1 < t0)
		return (t1);
	else
		return (t0);
}

static float	pick_valid_t(t_cam_ray *ray, t_cylinder *cy, float t0, float t1)
{
	t_v3d	hit_point;
	t_v3d	base_to_point;
	float	h_on_axis;

	if (t0 > EPSILON)
	{
		hit_point = add(ray->coord, sc_mult(ray->v_dir, t0));
		base_to_point = sub(hit_point, cy->coord);
		h_on_axis = dot_product(base_to_point, cy->ori);
		if (h_on_axis >= 0 && h_on_axis <= cy->h)
			return (t0);
	}
	if (t1 > EPSILON)
	{
		hit_point = add(ray->coord, sc_mult(ray->v_dir, t1));
		base_to_point = sub(hit_point, cy->coord);
		h_on_axis = dot_product(base_to_point, cy->ori);
		if (h_on_axis >= 0 && h_on_axis <= cy->h)
			return (t1);
	}
	return (-1);
}

t_v3d	cy_normal(t_v3d hit_point, t_cylinder *cy)
{
	t_v3d	base_to_hit;
	t_v3d	ray_vector;
	t_v3d	normal;
	float	h_on_axis;
	float	ray_length;

	base_to_hit = sub(hit_point, cy->coord);
	h_on_axis = dot_product(base_to_hit, cy->ori);
	ray_vector = sub(base_to_hit, sc_mult(cy->ori, h_on_axis));
	ray_length = sqrt(dot_product(ray_vector, ray_vector));
	normal.x = ray_vector.x / ray_length;
	normal.y = ray_vector.y / ray_length;
	normal.z = ray_vector.z / ray_length;
	return (normal);
}

float	cy_inter_body(t_cam_ray *ray, t_cylinder *cy, t_v3d *normal)
{
	float	quad[4];
	float	dist[2];
	t_v3d	oc;
	float	t;

	oc = sub(ray->coord, cy->coord);
	quad[0] = dot_product(ray->v_dir, ray->v_dir)
		- pow(dot_product(ray->v_dir, cy->ori), 2);
	quad[1] = 2 * (dot_product(ray->v_dir, oc)
			- (dot_product(ray->v_dir, cy->ori) * dot_product(oc, cy->ori)));
	quad[2] = dot_product(oc, oc)
		- pow(dot_product(oc, cy->ori), 2) - pow(cy->r, 2);
	quad[3] = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (quad[3] < 0)
		return (-1);
	dist[0] = (-quad[1] - sqrt(quad[3])) / (2 * quad[0]);
	dist[1] = (-quad[1] + sqrt(quad[3])) / (2 * quad[0]);
	t = pick_valid_t(ray, cy, dist[0], dist[1]);
	if (t < 0)
		return (-1);
	if (normal)
		*normal = cy_normal(add(ray->coord, sc_mult(ray->v_dir, t)), cy);
	return (t);
}

float	cy_inter_cap(t_cam_ray *ray, t_cylinder *cy, bool top, t_v3d *normal)
{
	t_v3d	center;
	float	denom;
	float	t;
	t_v3d	hit;
	float	dist2;

	if (top)
		center = add(cy->coord, sc_mult(cy->ori, cy->h));
	else
		center = cy->coord;
	denom = dot_product(ray->v_dir, cy->ori);
	if (fabs(denom) < EPSILON)
		return (-1);
	t = dot_product(sub(center, ray->coord), cy->ori) / denom;
	if (t <= EPSILON)
		return (-1);
	hit = add(ray->coord, sc_mult(ray->v_dir, t));
	dist2 = dot_product(sub(hit, center), sub(hit, center));
	if (dist2 > cy->r * cy->r)
		return (-1);
	if (normal && top)
		*normal = cy->ori;
	else if (normal)
		*normal = sc_mult(cy->ori, -1);
	return (t);
}
