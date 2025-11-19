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
	float	res;
	float	fract;
	float	div;
	float	sign;

	div = 1.0;
	fract = 0.0;
	sign = 1.0;
	if (*str && str[0] == '-')
		sign *= -1.0;
	res = (float)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			div *= 10.0;
			fract += (*str - '0') / div;
		}
		str++;
	}
	fract *= sign;
	return (res + fract);
}

int	safe_float(char *s, float *out)
{
	int		digits;
	int		i;
	float	v;

	digits = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			digits++;
		i++;
	}
	if (digits > 38)
		return (print_error("Float overflow"));
	v = s_to_f(s);
	if (!isfinite(v))
		return (print_error("Float overflow"));
	*out = v;
	return (1);
}
