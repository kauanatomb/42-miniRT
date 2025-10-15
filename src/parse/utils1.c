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

int	parse_vector(char *str, t_v3d ori)
{
	char	**tab;

	tab = ft_split(str, ',');
	if (!tab)
		return (print_error("Malloc failed"));
	if (count_elements(tab) != 3)
		return (free_tab(tab), print_error("Orientation needs 3 values"));
	if (!is_float(tab[0]) || !is_float(tab[1]) || !is_float(tab[2]))
		return (free_tab(tab), print_error("Invalid float format orientation"));
	ori.x = s_to_f(tab[0]);
	ori.y = s_to_f(tab[1]);
	ori.z = s_to_f(tab[2]);
	if (ori.x < -1 || ori.x > 1 || ori.y < -1 || ori.y > 1
		|| ori.z < -1 || ori.z > 1)
		return (free_tab(tab), print_error("Wrong orientation vector range"));
	free_tab(tab);
	return (1);
}
