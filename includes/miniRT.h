/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/11/11 14:43:13 by falatrac         ###   ########.fr       */
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

# define WIN_W 1200
# define WIN_H 800
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define Q 113
# define E 101
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

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
void	init_camera(t_camera *cam);
int		launch_cam_rays(t_rt *rt);
int		inter_closest(t_rt *rt, t_cam_ray *cam_ray);
float	dot_product(t_v3d a, t_v3d b);
t_v3d	add(t_v3d a, t_v3d b);
t_v3d	sub(t_v3d a, t_v3d b);
t_v3d	cross(t_v3d a, t_v3d b);
t_v3d	sc_mult(t_v3d a, float scalar);
t_v3d	normalize(t_v3d v);
float	bhaskara(float a, float b, float c);
t_v3d	cy_normal(t_v3d hit_point, t_cylinder *cy);
float	cy_inter_body(t_cam_ray *ray, t_cylinder *cy, t_v3d *normal);
t_color	get_obj_color(t_inter inter);
int		rgb_to_int(t_color rgb);
void	my_mlx_pixel_put(t_img img, int x, int y, int color);
t_v3d	rotate_y(t_v3d v, float angle);
float	cy_inter_cap(t_cam_ray *ray, t_cylinder *cy, bool top, t_v3d *normal);
t_color compute_light(t_rt *rt, t_inter inter);

#endif