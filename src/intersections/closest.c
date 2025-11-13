/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/11/13 14:59:28 by falatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	plane_inter(t_cam_ray *cam_ray, t_objects *obj, t_inter *tmp)
{
	float	denom;
	float	t;
	t_plane	*plane;

	tmp->dist = INFINITY;
	tmp->obj = NULL;
	plane = &obj->fig.pl;
	plane->ori = normalize(plane->ori);
	denom = dot_product(plane->ori, cam_ray->v_dir);
	if (fabs(denom) < EPSILON)
		return (0);
	t = dot_product(sub(plane->coord, cam_ray->coord), plane->ori) / denom;
	if (t < EPSILON)
		return (0);
	tmp->dist = t;
	tmp->obj = obj;
	tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, t));
	tmp->normal = plane->ori;
	tmp->point = add(tmp->point, sc_mult(tmp->normal, EPSILON));
	return (1);
}

int	sphere_inter(t_cam_ray *cam_ray, t_objects *obj, t_inter *tmp)
{
	float		t;
	t_v3d		oc;
	t_sphere	*sphere;

	tmp->dist = INFINITY;
	tmp->obj = NULL;
	sphere = &obj->fig.sp;
	oc = sub(cam_ray->coord, sphere->coord);
	t = bhaskara(dot_product(cam_ray->v_dir, cam_ray->v_dir), 2.0
			* dot_product(oc, cam_ray->v_dir), dot_product(oc, oc)
			- sphere->r * sphere->r);
	if (t < EPSILON)
		return (0);
	tmp->obj = obj;
	tmp->dist = t;
	tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, t));
	tmp->normal = normalize(sub(tmp->point, sphere->coord));
	return (1);
}

int	cy_inter(t_cam_ray *cam_ray, t_objects *obj, t_inter *tmp)
{
	t_cylinder	*cy;
	t_v3d		n_best;
	t_v3d		n_tmp;
	float		t_best;
	float		t;

	tmp->dist = INFINITY;
	tmp->obj = NULL;
	cy = &obj->fig.cy;
	t_best = INFINITY;
	t = cy_inter_body(cam_ray, cy, &n_tmp);
	update_hit(t, &t_best, &n_best, &n_tmp);
	t = cy_inter_cap(cam_ray, cy, true, &n_tmp);
	update_hit(t, &t_best, &n_best, &n_tmp);
	t = cy_inter_cap(cam_ray, cy, false, &n_tmp);
	update_hit(t, &t_best, &n_best, &n_tmp);
	if (t_best < INFINITY)
	{
		tmp->dist = t_best;
		tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, t_best));
		tmp->normal = normalize(n_best);
		tmp->obj = obj;
		return (1);
	}
	return (0);
}

int	inter_object(t_cam_ray *ray, t_objects *obj, t_inter *tmp)
{
	if (obj->type == PLANE)
		return (plane_inter(ray, obj, tmp));
	else if (obj->type == SPHERE)
		return (sphere_inter(ray, obj, tmp));
	else if (obj->type == CYLINDER)
		return (cy_inter(ray, obj, tmp));
	return (0);
}

int	inter_closest(t_rt *rt, t_cam_ray *cam_ray)
{
	t_inter		closest;
	t_inter		tmp;
	t_objects	*curr_obj;

	tmp.dist = INFINITY;
	tmp.obj = NULL;
	closest.dist = INFINITY;
	closest.obj = NULL;
	curr_obj = rt->sc->obj;
	while (curr_obj)
	{
		inter_object(cam_ray, curr_obj, &tmp);
		if (tmp.dist < closest.dist)
			closest = tmp;
		curr_obj = curr_obj->next;
	}
	if (!closest.obj)
		return (0);
	cam_ray->inter = closest;
	return (1);
}
