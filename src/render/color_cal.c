/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_cal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	color_mult(t_color c1, t_color c2)
{
	return ((t_color)
		{
			.r = c1.r * c2.r,
			.g = c1.g * c2.g,
			.b = c1.b * c2.b,
		}
	);
}

t_color	color_add(t_color c1, t_color c2)
{
	return ((t_color)
		{
			.r = c1.r + c2.r,
			.g = c1.g + c2.g,
			.b = c1.b + c2.b,
		}
	);
}

t_color	color_scale(t_color c, float k)
{
	return ((t_color){c.r * k, c.g * k, c.b * k});
}
