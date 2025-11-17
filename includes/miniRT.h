/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/11/17 13:21:21 by falatrac         ###   ########.fr       */
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

# define WIN_W 1910
# define WIN_H 1000
# define EPSILON 1e-4
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define Q 113
# define E 101
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define L_FORWARD   105  // 'i'
# define L_BACKWARD  107  // 'k'
# define L_LEFT      106  // 'j'
# define L_RIGHT     108  // 'l'
# define L_UP        117  // 'u'
# define L_DOWN      111  // 'o' 
# define SHININESS 60 //32 plastic 128 metal

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
float	cy_inter_cap(t_cam_ray *ray, t_cylinder *cy, bool top, t_v3d *normal);
t_color	compute_light(t_rt *rt, t_inter inter);
t_color	color_mult(t_color c1, t_color c2);
t_color	color_add(t_color c1, t_color c2);
int		inter_object(t_cam_ray *ray, t_objects *obj, t_inter *tmp);
t_color	color_scale(t_color c, float k);
void	update_hit(float t, float *t_best, t_v3d *n_best, t_v3d *n_tmp);
void	handle_light_movement(int keycode, t_light *l, t_camera *cam);
void	handle_cam_moviment(int keycode, t_camera *cam);
t_v3d	rotate_axis(t_v3d v, t_v3d axis, float angle);

#endif