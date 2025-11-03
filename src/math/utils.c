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

float	dot_product(t_v3d a, t_v3d b)
{
	return (a.x * b.x + a.y * b.y + a.z + b.z);
}

t_v3d	add(t_v3d a, t_v3d b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_v3d	sc_mult(t_v3d a, float scalar)
{
	a.x *= scalar;
	a.y *= scalar;
	a.z *= scalar;
	return (a);
}

t_v3d	sub(t_v3d a, t_v3d b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}
