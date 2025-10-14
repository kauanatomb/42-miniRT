/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ambiance_parsing(char *line, t_rt *rt)
{
	char	**tab;

	if (rt->sc->has_amb)
		return (print_error("Too many ambiance lights (1 or 0 needed)"));
	tab = ft_split(line, ' ');
	if (!tab)
		return (print_error("Malloc failed"));
	if (count_elements(tab) != 3)
		return (print_error("Wrong number of elements for ambiance"));
	rt->sc->has_amb = true;
	return (1);
}
