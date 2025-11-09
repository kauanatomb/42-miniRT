/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	plane_inter(t_cam_ray *cam_ray, t_objects *obj, t_inter *tmp)
{
	float	denom;
	float	t;
	t_plane	*plane;

	tmp->dist = INFINITY;
	plane = &obj->fig.pl;
	plane->ori = normalize(plane->ori);
	denom = dot_product(plane->ori, cam_ray->v_dir);
	if (fabs(denom) <= 0)
		return ;
	t = dot_product(sub(plane->coord, cam_ray->coord), plane->ori) / denom;
	if (t < 1e-4)
		return ;
	tmp->dist = t;
	tmp->obj = obj;
	tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, t));
	tmp->normal = plane->ori;
	tmp->point = add(tmp->point, sc_mult(tmp->normal, 1e-4));
}

void	sphere_inter(t_cam_ray *cam_ray, t_objects *obj, t_inter *tmp)
{
	float		t;
	t_v3d		oc;
	t_sphere	*sphere;

	tmp->dist = INFINITY;
	sphere = &obj->fig.sp;
	oc = sub(cam_ray->coord, sphere->coord);
	t = bhaskara(dot_product(cam_ray->v_dir, cam_ray->v_dir), 2.0
			* dot_product(oc, cam_ray->v_dir), dot_product(oc, oc)
			- sphere->r * sphere->r);
	if (t < 0)
		return ;
	tmp->obj = obj;
	tmp->dist = t;
	tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, t));
	tmp->normal = normalize(sub(tmp->point, sphere->coord));
}

void	cy_inter(t_cam_ray *cam_ray, t_objects *obj, t_inter *tmp)
{
	t_v3d		oc;
	t_cylinder	*cy;

	tmp->dist = INFINITY;
	cy = &obj->fig.cy;
	oc.x = cam_ray->coord.x - cy->coord.x;
	oc.y = cam_ray->coord.y - cy->coord.y;
	oc.z = cam_ray->coord.z - cy->coord.z;
	if (!quad_cy(cam_ray, tmp, cy, oc))
		return ;
	cap_cy(cam_ray, cy, tmp);
	tmp->obj = obj;
	tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, tmp->dist));
	tmp->normal = cy_normal(tmp->point, cy);
}

int	inter_closest(t_rt *rt, t_cam_ray *cam_ray)
{
	t_inter		closest;
	t_inter		tmp;
	t_objects	*curr_obj;
	int			hit;

	hit = 0;
	tmp.dist = INFINITY;
	tmp.obj = NULL;
	closest.dist = INFINITY;
	curr_obj = rt->sc->obj;
	while (curr_obj)
	{
		if (curr_obj->type == PLANE)
			plane_inter(cam_ray, curr_obj, &tmp);
		else if (curr_obj->type == SPHERE)
			sphere_inter(cam_ray, curr_obj, &tmp);
		else if (curr_obj->type == CYLINDER)
			cy_inter(cam_ray, curr_obj, &tmp);
		if (tmp.dist < closest.dist)
		{
			closest = tmp;
			hit = 1;
		}
		curr_obj = curr_obj->next;
	}
	if (hit)
		cam_ray->inter = closest;
	return (hit);
}
