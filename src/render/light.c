/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:53:49 by falatrac          #+#    #+#             */
/*   Updated: 2025/11/17 12:43:59 by falatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	ambient_light(t_color obj, t_color ambient_light, float ratio)
{
	t_color	result;

	result.r = obj.r * ratio * (ambient_light.r / 255.0);
	result.g = obj.g * ratio * (ambient_light.g / 255.0);
	result.b = obj.b * ratio * (ambient_light.b / 255.0);
	return (result);
}

int	is_shadowed(t_scene *sc, t_inter inter)
{
	t_v3d		light_dir;
	float		light_distance;
	t_cam_ray	ray_shadow;
	t_objects	*curr_obj;
	t_inter		tmp;

	light_dir = sub(sc->light.coord, inter.point);
	light_distance = sqrt(dot_product(light_dir, light_dir));
	ray_shadow.coord = add(inter.point, sc_mult(inter.normal, EPSILON));
	ray_shadow.v_dir = normalize(light_dir);
	curr_obj = sc->obj;
	tmp.dist = INFINITY;
	tmp.obj = NULL;
	while (curr_obj)
	{
		if (curr_obj != inter.obj && inter_object(&ray_shadow, curr_obj, &tmp))
		{
			if (tmp.dist > EPSILON && tmp.dist < light_distance)
				return (1);
		}
		curr_obj = curr_obj->next;
	}
	return (0);
}

t_color	compute_light(t_rt *rt, t_inter inter)
{
	t_ambient	amb;
	t_color		color;
	t_light		light;
	t_v3d		light_dir;
	t_color		diffuse;

	amb = rt->sc->amb;
	color = ambient_light(get_obj_color(inter), amb.color, amb.ratio);
	if (rt->sc->has_light && !is_shadowed(rt->sc, inter))
	{
		light = rt->sc->light;
		light_dir = normalize(sub(light.coord, inter.point));
		diffuse = color_scale(get_obj_color(inter), (light.ratio
					* fmax(0.0, dot_product(inter.normal, light_dir))));
		color = color_add(color, diffuse);
	}
	return (color);
}
