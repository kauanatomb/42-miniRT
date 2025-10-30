/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matriz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	bhaskara(float a, float b, float c)
{
	float	delta;
	float	t0;
	float	t1;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1);
	t0 = (-b - sqrt(delta)) / (2 * a);
	t1 = (-b + sqrt(delta)) / (2 * a);
	if (t0 < 0)
		t0 = t1;
	if (t0 < 0)
		return (-1);
	else if (t1 >= 0 && t1 < t0)
		return (t1);
	else
		return (t0);
}

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