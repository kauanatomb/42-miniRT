/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	clamp_color(int one_color)
{
	if (one_color < 0)
		return (0);
	if (one_color > 255)
		return (255);
	return (one_color);
}

t_color	get_obj_color(t_inter inter)
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

	r = clamp_color(c.r);
	g = clamp_color(c.g);
	b = clamp_color(c.b);
	return ((r << 16) | (g << 8) | b);
}
