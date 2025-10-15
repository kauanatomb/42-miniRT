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
# include <stdbool.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_v3d
{
	float	x;
	float	y;
	float	z;
}	t_v3d;

typedef struct s_camera
{
	float	fov;
	t_v3d	coord;
	t_v3d	ori;
}	t_camera;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_scene
{
	t_ambient	amb;
	t_camera	cam;
	// t_light		light;
	// t_objects	*obj;
	bool		has_amb;
	bool		has_cam;
	bool		has_light;
}	t_scene;

typedef struct s_rt
{
	int		win_w;
	int		win_h;
	// t_mlbx	*mlbx;
	t_scene	*sc;
}	t_rt;

int		print_error(char *error_message);
void	clean_rt_scene(t_rt *rt);
int		file_parsing(char *file, t_rt *rt);
int		ambiance_parsing(char *line, t_rt *rt);
int		camera_parsing(char *line, t_rt *rt);
int 	count_elements(char **ar);
int 	parse_ratio(char *str, float *ratio);
int		parse_color(char *str, t_color *color);
int		parse_coord(char *str, t_v3d coord);
int		parse_vector(char *str, t_v3d ori);
int		parse_general(char *str, float fov, int i);
void    free_tab(char **tab);
int		is_float(char *str);
float	s_to_f(char *str);

#endif