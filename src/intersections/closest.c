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
	if (t < EPSILON)
		return ;
	tmp->dist = t;
	tmp->obj = obj;
	tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, t));
	tmp->normal = plane->ori;
	tmp->point = add(tmp->point, sc_mult(tmp->normal, EPSILON));
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
	t_cylinder	*cy;
	t_v3d		n_best;
	float		t_best;
	float		t;

	t_best = INFINITY;
	cy = &obj->fig.cy;
	t = cy_inter_body(cam_ray, cy, &n_best);
	if (t > 0 && t < t_best)
		t_best = t;
	t = cy_inter_cap(cam_ray, cy, true, &n_best);
	if (t > 0 && t < t_best)
		t_best = t;
	t = cy_inter_cap(cam_ray, cy, false, &n_best);
	if (t > 0 && t < t_best)
		t_best = t;
	if (t_best < INFINITY)
	{
		tmp->dist = t_best;
		tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, t_best));
		tmp->normal = n_best;
		tmp->obj = obj;
	}
}

int	inter_object(t_cam_ray *ray, t_objects *obj, t_inter *tmp)
{
	if (obj->type == PLANE)
		plane_inter(ray, obj, tmp);
	else if (obj->type == SPHERE)
		sphere_inter(ray, obj, tmp);
	else if (obj->type == CYLINDER)
		cy_inter(ray, obj, tmp);
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
