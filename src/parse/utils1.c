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
	float	len;

	tab = ft_split(str, ',');
	if (!tab)
		return (print_error("Malloc failed"));
	if (count_elements(tab) != 3)
		return (free_tab(tab), print_error("Orientation needs 3 values"));
	if (!is_float(tab[0]) || !is_float(tab[1]) || !is_float(tab[2]))
		return (free_tab(tab), print_error("Invalid float format orientation"));
	ori->x = s_to_f(tab[0]);
	ori->y = s_to_f(tab[1]);
	ori->z = s_to_f(tab[2]);
	if (ori->x < -1 || ori->x > 1 || ori->y < -1 || ori->y > 1
		|| ori->z < -1 || ori->z > 1)
		return (free_tab(tab), print_error("Wrong orientation vector range"));
	len = sqrt(ori->x * ori->x + ori->y * ori->y + ori->z * ori->z);
	if (fabs(len - 1.0) > 1e-3)
		return (free_tab(tab), print_error("Vector not normalized"));
	free_tab(tab);
	return (1);
}

int	parse_general(char *str, float *p, int i)
{
	if (!is_float(str))
		return (print_error("Invalid float format"));
	*p = s_to_f(str);
	if (i == 1)
	{
		if (*p > 180 || *p < 0)
			return (print_error("Invalid range for FOV"));
	}
	else if (i == 2)
		*p = *p / 2;
	else
	{
		if (*p < 0)
			return (print_error("Invalid diameter/height: cannot be negative"));
	}
	return (1);
}

void	add_obj_to_rt(t_rt *rt, t_objects *obj_created)
{
	obj_created->next = rt->sc->obj;
	rt->sc->obj = obj_created;
}
