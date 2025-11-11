/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:53:49 by falatrac          #+#    #+#             */
/*   Updated: 2025/11/11 14:42:31 by falatrac         ###   ########.fr       */
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

t_color	compute_light(t_rt *rt, t_inter inter)
{
	t_ambient	amb;
	t_color		color;

	amb = rt->sc->amb;
	color = ambient_light(get_obj_color(inter), amb.color, amb.ratio);
	return (color);
}
