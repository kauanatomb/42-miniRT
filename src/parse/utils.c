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

int	count_elements(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	parse_ratio(char *str, float *ratio)
{
	if (!is_float(str))
		return (print_error("Invalid float format ratio"));
	*ratio = s_to_f(str);
	if (*ratio >= 0 && *ratio <= 1)
		return (1);
	else
		return (print_error("Radio out of range [0.0,1.0]"));
	return (1);
}

int	parse_color(char *str, t_color *color)
{
	char	**tab;

	tab = ft_split(str, ',');
	if (!tab)
		return (print_error("Malloc failed"));
	if (count_elements(tab) != 3)
		return (free_tab(tab), print_error("RGB needs 3 values"));
	color->r = ft_atoi(tab[0]);
	color->g = ft_atoi(tab[1]);
	color->b = ft_atoi(tab[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (free_tab(tab), print_error("Wrong RGB range"));
	free_tab(tab);
	return (1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
