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
	{
		free_tab(tab);
		return (print_error("Wrong number of elements for ambiance"));
	}
	rt->sc->has_amb = true;
	if (!parse_ratio(tab[1], &rt->sc->amb.ratio))
		return (free_tab(tab), 0);
	if (!parse_color(tab[2], &rt->sc->amb.color))
		return (free_tab(tab), 0);
	free_tab(tab);
	return (1);
}

int	camera_parsing(char *line, t_rt *rt)
{
	char	**tab;

	if (rt->sc->has_cam)
		return (print_error("Too many cameras (1 or 0 needed)"));
	tab = ft_split(line, ' ');
	if (!tab)
		return (print_error("Malloc failed"));
	if (count_elements(tab) != 4)
		return (free_tab(tab), print_error("Wrong elements number for camera"));
	rt->sc->has_cam = true;
	if (!parse_coord(tab[1], rt->sc->cam.coord))
		return (free_tab(tab), 0);
	if (!parse_vector(tab[2], rt->sc->cam.ori))
		return (free_tab(tab), 0);
	// if (!parse_general(tab[1], rt->sc->cam->fov))
	// 	return (free_tab(tab), 0);
	free_tab(tab);
	return (1);
}
