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
# include <math.h>
# include "structures.h"

int		print_error(char *error_message);
void	clean_rt_scene(t_rt *rt);
int		file_parsing(char *file, t_rt *rt);
int		ambiance_parsing(char *line, t_rt *rt);
int		camera_parsing(char *line, t_rt *rt);
int		light_parsing(char *line, t_rt *rt);
int		count_elements(char **ar);
int		parse_ratio(char *str, float *ratio);
int		parse_color(char *str, t_color *color);
int		parse_coord(char *str, t_v3d *coord);
int		parse_vector(char *str, t_v3d *ori);
int		parse_general(char *str, float *fov, int i);
int		sphere_parsing(char *line, t_rt *rt);
int		plane_parsing(char *line, t_rt *rt);
int		cy_parsing(char *line, t_rt *rt);
void	free_tab(char **tab);
int		is_float(char *str);
float	s_to_f(char *str);
void	add_obj_to_rt(t_rt *rt, t_objects *obj_created);
int		make_window(t_rt *rt);
int		launch_cam_rays(t_rt *rt);
int		inter_closest(t_rt *rt, t_cam_ray *cam_ray);
float	dot_product(t_v3d a, t_v3d b);
t_v3d	add(t_v3d a, t_v3d b);
t_v3d	sub(t_v3d a, t_v3d b);
t_v3d	sc_mult(t_v3d a, float scalar);
t_v3d	normalize(t_v3d v);
float	bhaskara(float a, float b, float c);
t_v3d	cy_normal(t_v3d hit_point, t_cylinder *cy);
int		quad_cy(t_cam_ray *ray, t_inter *tmp, t_cylinder *cy, t_v3d oc);

#endif