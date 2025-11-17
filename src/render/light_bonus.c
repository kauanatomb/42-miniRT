/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:53:49 by falatrac          #+#    #+#             */
/*   Updated: 2025/11/17 11:59:23 by falatrac         ###   ########.fr       */
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

static t_color	compute_diffuse(t_inter inter, t_light light, t_v3d light_dir)
{
	t_color	obj_col;
	float	dot_nl;
	float	intensity;

	obj_col = get_obj_color(inter);
	dot_nl = fmax(0.0f, dot_product(inter.normal, light_dir));
	intensity = light.ratio * dot_nl / 255.0f;
	return (color_scale(color_mult(obj_col, light.color), intensity));
}

static t_color	compute_specular(t_rt *rt, t_light light,
				t_inter inter, t_v3d light_dir)
{
	t_v3d	view_dir;
	t_v3d	reflect_dir;
	float	dot_nl;
	float	dot_rv;
	float	spec_factor;

	view_dir = normalize(sub(rt->sc->cam.coord, inter.point));
	dot_nl = dot_product(inter.normal, light_dir);
	if (dot_nl <= 0.0f)
		return ((t_color){0, 0, 0});
	reflect_dir = sc_mult(inter.normal, 2.0f * dot_nl);
	reflect_dir = sub(reflect_dir, light_dir);
	reflect_dir = normalize(reflect_dir);
	dot_rv = dot_product(reflect_dir, view_dir);
	if (dot_rv <= 0.0f)
		return ((t_color){0, 0, 0});
	spec_factor = powf(dot_rv, SHININESS);
	return (color_scale(light.color, light.ratio * spec_factor));
}

t_color	compute_light(t_rt *rt, t_inter inter)
{
	t_color	color;
	t_v3d	light_dir;
	t_color	diffuse;
	t_color	specular;

	color = ambient_light(get_obj_color(inter),
			rt->sc->amb.color, rt->sc->amb.ratio);
	if (rt->sc->has_light && !is_shadowed(rt->sc, inter))
	{
		light_dir = normalize(sub(rt->sc->light.coord, inter.point));
		diffuse = compute_diffuse(inter, rt->sc->light, light_dir);
		color = color_add(color, diffuse);
		specular = compute_specular(rt, rt->sc->light, inter, light_dir);
		color = color_add(color, specular);
	}
	return (color);
}
