/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_color(t_inter inter)
{
	t_color	background;

	background.r = 0;
	background.g = 0;
	background.b = 0;
	if (!inter.obj)
		return (background);
	else if (inter.obj->type == PLANE)
		inter.c = inter.obj->fig.pl.color;
	else if (inter.obj->type == SPHERE)
		inter.c = inter.obj->fig.sp.color;
	else if (inter.obj->type == CYLINDER)
		inter.c = inter.obj->fig.cy.color;
	return (inter.c);
}

int	rgb_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = clamp(c.r, 0, 255);
	g = clamp(c.g, 0, 255);
	b = clamp(c.b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

t_color ambient_light(t_color obj, t_color ambient_light, float ratio)
{
    t_color result;

    result.r = obj.r * ratio * (ambient_light.r / 255.0);
    result.g = obj.g * ratio * (ambient_light.g / 255.0);
    result.b = obj.b * ratio * (ambient_light.b / 255.0);

    return result;
}


// int	is_shadowed(t_scene *sc, t_inter inter)
// {
// 	t_v3d		light_dir;
// 	float		light_distance;
// 	t_cam_ray	ray_shadow;
// 	t_light		light;

// 	light = sc->light;
// 	light_dir = sub(light.coord, inter.point);
// 	light_distance = sqrt(dot_product(light_dir, light_dir));
// 	ray.coord = add(inter.point, sc_mult(inter.normal, EPSILON));
// 	ray.v_dir = normalize(light_dir);
// 	return ()
// }

t_color	compute_light(t_rt *rt, t_cam_ray *ray)
{
	t_color	color;

	color = ambient_light(get_color(ray->inter), rt->sc->amb.color, rt->sc->amb.ratio);
	// if (rt->sc->has_light)
	// {
	// 	if (!is_shadowed(rt->sc, ray->inter))
	// 		color = color_add(color, diffuse(rt->sc->light, ray->inter, rt->sc->light.ratio));
	// }
	return (color);
}