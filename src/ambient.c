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

static int	clmap8(int one_color)
{
	if (one_color < 0)
		return (0);
	if (one_color > 255)
		return (255);
	return (one_color);
}

static t_color	color_scale(t_color c, float s)
{
	t_color	out;

	out.r = clmap8((int)(c.r * s));
	out.g = clmap8((int)(c.g * s));
	out.b = clmap8((int)(c.b * s));
	return (out);
}

static t_color	color_mul_per_channel(t_color a, t_color b)
{
	t_color	out;

	out.r = clmap8((a.r * b.r) / 255);
	out.g = clmap8((a.g * b.g) / 255);
	out.b = clmap8((a.b * b.b) / 255);
	return (out);
}

static t_color	get_obj_color(t_inter inter)
{
	t_color	backgroud;

	backgroud.r = 0;
	backgroud.g = 0;
	backgroud.b = 0;
	if (!inter.obj)
		return (backgroud);
	if (inter.obj->type == PLANE)
		return (inter.obj->fig.pl.color);
	else if (inter.obj->type == SPHERE)
		return (inter.obj->fig.sp.color);
	else if (inter.obj->type == CYLINDER)
		return (inter.obj->fig.cy.color);
	return (backgroud);
}

t_color	shade_ambient(t_rt *rt, t_inter inter)
{
	t_color	obj;
	t_color	mixed;

	if (!inter.obj)
		return ((t_color){0, 0, 0});
	obj = get_obj_color(inter);
	mixed = color_mul_per_channel(obj, rt->sc->amb.color);
	return (color_scale(mixed, rt->sc->amb.ratio));
}
