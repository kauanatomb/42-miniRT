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

int	rgb_to_int(t_color rgb)
{
	return (((rgb.r & 0xff) << 16) | ((rgb.g & 0xff) << 8) | (rgb.b & 0xff));
}