/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	print_error(char *error_message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

void	free_objects(t_objects *objs)
{
	t_objects	*tmp;

	while (objs->next)
	{
		tmp = objs->next;
		free(objs);
		objs = tmp;
	}
	free(objs);
}

void	clean_rt_scene(t_rt *rt)
{
	if (!rt)
		return ;
	if (rt->sc)
	{
		if (rt->sc->obj)
			free_objects(rt->sc->obj);
		if (rt->mlbx)
		{
			free(rt->mlbx->mlx);
			free(rt->mlbx);
		}
		free(rt->sc);
	}
	free(rt);
}
