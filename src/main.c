/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_rt	*rt;

	if (argc != 2)
	{
		print_error("Args needed: ./miniRT [scene_file]");
		return (1);
	}
	rt = ft_calloc(sizeof(t_rt), 1);
	if (!rt)
		return (print_error("Malloc error rt"), 1);
	rt->win_w = 1200;
	rt->win_h = 800;
	if (!file_parsing(argv[1], rt))
		return (clean_rt_scene(rt), 1);
	make_window(rt);
	return (0);
}
