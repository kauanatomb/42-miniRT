/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
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
	if (fabs(denom) < 1e-6)
		return ;// demon is paralel (without inter)
	t = dot_product(sub(plane->coord, cam_ray->coord), plane->ori) / denom;
	if (t < 1e-4)
		return ;// behind the camera (withou inter)
	tmp->dist = t;
	tmp->obj = obj;
	tmp->point = add(cam_ray->coord, sc_mult(cam_ray->v_dir, t));
	tmp->point = add(tmp->point, sc_mult(tmp->normal, 1e-4));
	tmp->normal = plane->ori;
}

int	inter_closest(t_rt *rt, t_cam_ray *cam_ray)
{
	t_inter		closest;
	t_inter		tmp;
	t_objects	*curr_obj;

	tmp.dist = INFINITY;
	closest.dist = INFINITY;
	curr_obj = rt->sc->obj;
	while (curr_obj)
	{
		if (curr_obj->type == PLANE)
			plane_inter(cam_ray, curr_obj, &tmp);
		if (tmp.dist < closest.dist)
			closest = tmp;
		curr_obj = curr_obj->next;
	}
	cam_ray->inter = malloc(sizeof(t_inter));
	if (!cam_ray->inter)
		return (print_error("Malloc error intersections"));
	*(cam_ray->inter) = closest;
	return (1);
}
