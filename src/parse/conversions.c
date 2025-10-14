/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_float(char *str)
{
	bool	has_dot;
	int		i;

	i = 0;
	has_dot = false;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && !has_dot)
			i++;
		else if (str[i] == '.' && str[i + 1])
		{
			if (has_dot)
				return (0);
			has_dot = true;
			i++;
		}
		else if (str[i] >= '0' && str[i] <= '9' && has_dot)
			i++;
		else
			return (0);
	}
	return (1);
}

float	s_to_f(char *str)
{
	(void)str;
	return (1);
}