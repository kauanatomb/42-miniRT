/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

int	sphere_parsing(char *line, t_rt *rt)
{
	char		**tab;
	t_objects	*obj;

	tab = ft_split(line, ' ');
	if (!tab)
		return (print_error("Malloc failed"));
	if (count_elements(tab) != 4)
		return (free_tab(tab), print_error("Wrong number of elements(sphere)"));
	obj = malloc(sizeof(t_objects));
	if (!obj)
		return (free_tab(tab), print_error("Malloc failed"));
	obj->type = SPHERE;
	obj->next = NULL;
	if (!parse_coord(tab[1], &obj->fig.sp.coord))
		return (free_tab(tab), 0);
	if (!parse_general(tab[2], &obj->fig.sp.r, 0))
		return (free_tab(tab), 0);
	if (!parse_color(tab[3], &obj->fig.sp.color))
		return (free_tab(tab), 0);
	add_obj_to_rt(rt, obj);
	free_tab(tab);
	return (1);
}
