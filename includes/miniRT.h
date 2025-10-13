/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>

// typedef struct s_scene
// {
// 	t_ambient	amb;
// 	t_camera	cam;
// 	t_light		light;
// 	t_objects	*obj;
// }	t_scene;

typedef struct s_rt
{
	int		win_w;
	int		win_h;
	// t_mlbx	*mlbx;
	// t_scene	*sc;
}	t_rt;

int		file_parsing(char *file, t_rt *rt);
int		print_error(char *error_message);

#endif