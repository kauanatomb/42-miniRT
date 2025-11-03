/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "miniRT.h"

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
	t_v3d	right;
	t_v3d	up;
	t_v3d	forward;
}	t_camera;

typedef struct s_light
{
	t_v3d	coord;
	float	ratio;
	t_color	color;
}	t_light;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_sphere
{
	t_v3d	coord;
	float	r;
	t_color	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_v3d	coord;
	t_v3d	ori;
	float	r;
	float	h;
	t_color	color;
}	t_cylinder;

typedef struct s_plane
{
	t_v3d	coord;
	t_v3d	ori;
	t_color	color;
}	t_plane;

enum e_figure
{
	SPHERE,
	PLANE,
	CYLINDER
};

union u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

typedef struct s_objects
{
	enum e_figure		type;
	union u_figures		fig;
	struct s_objects	*next;
}	t_objects;

typedef struct s_scene
{
	t_ambient	amb;
	t_camera	cam;
	t_light		light;
	t_objects	*obj;
	bool		has_amb;
	bool		has_cam;
	bool		has_light;
}	t_scene;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_p_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_mlbx
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}	t_mlbx;

typedef struct s_inter
{
	t_objects	*obj;
	float		dist;
	t_v3d		point;
	t_v3d		normal;
	t_color		c;
}	t_inter;

typedef struct s_cam_ray
{
	t_v3d	coord;
	t_v3d	v_dir;
	t_inter	inter;
}	t_cam_ray;

typedef struct s_rt
{
	int		win_w;
	int		win_h;
	t_mlbx	*mlbx;
	t_scene	*sc;
}	t_rt;

#endif