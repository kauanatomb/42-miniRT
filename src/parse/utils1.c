/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_vector(char *str, t_v3d *ori)
{
	char	**tab;

	tab = ft_split(str, ',');
	if (!tab)
		return (print_error("Malloc failed"));
	if (count_elements(tab) != 3)
		return (free_tab(tab), print_error("Orientation needs 3 values"));
	if (!is_float(tab[0]) || !is_float(tab[1]) || !is_float(tab[2]))
		return (free_tab(tab), print_error("Invalid float format orientation"));
	if (!safe_float(tab[0], &ori->x) || !safe_float(tab[1], &ori->y)
		|| !safe_float(tab[2], &ori->z))
		return (free_tab(tab), 0);
	free_tab(tab);
	if (ori->x < -1 || ori->x > 1 || ori->y < -1 || ori->y > 1
		|| ori->z < -1 || ori->z > 1)
		return (print_error("Orientation vector out of range [-1,1]"));
	if (ori->x == 0 && ori->y == 0 && ori->z == 0)
		return (print_error("Zero orientation vector is invalid"));
	*ori = normalize(*ori);
	return (1);
}

int	parse_general(char *str, float *p, int i)
{
	if (!is_float(str))
		return (print_error("Invalid float format"));
	if (!safe_float(str, p))
		return (0);
	if (i == 1)
	{
		if (*p > 180 || *p < 0)
			return (print_error("Invalid range for FOV"));
	}
	else if (i == 2)
		*p = *p / 2;
	if (*p < 0)
		return (print_error("Invalid diameter/height: cannot be negative"));
	return (1);
}

void	add_obj_to_rt(t_rt *rt, t_objects *obj_created)
{
	obj_created->next = rt->sc->obj;
	rt->sc->obj = obj_created;
}
