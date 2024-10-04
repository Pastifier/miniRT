/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:38:28 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/04 17:04:59by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "../LagAMat/include/lag.h"

enum e_object_types
{
	SPHERE,
	CYLINDER,
	PLANE,
	SPOT_LIGHT,
	POINT_LIGHT
};

typedef union u_color
{
	t_vec4s	v;
	struct
	{
		float	a;
		float	r;
		float	g;
		float	b;
	};
}	t_color;

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	sheen;
	double	reflective;
	double	transparency;
	double	refractive_index;
}	t_material;

typedef struct s_obj
{
	int		type;
	t_mat4s	rot;
	t_vec4s	trans;
	t_vec4s	scale;
	t_vec4s	orientation;
	union u_specs
	{
		struct s_sphere
		{
			double	radius;
		};
		struct s_plane
		{
			t_vec4s	normal;
		};
		struct s_cube
		{
			double	side_length;
		};
		struct s_cylinder
		{
			double	radius;
			double	min;
			double	max;
			bool	closed;
		};
	}	specs;
}	t_obj;

typedef struct s_ray
{
	t_vec4s	origin;
	t_vec4s	dir;
}	t_ray;

typedef struct s_intersection
{
	double	t;
	t_obj	*object;
	t_vec4s	itx_p;
	// subject to be grouped somewhere else:
	bool	shadowed;
	t_vec4s	p;
	t_vec4s	overp;
	t_vec4s	underp;
	t_vec4s	eyev;
	t_vec4s	normalv;
	t_vec4s	reflectv;
	int		inside;
	double	n1;
	double	n2;
}	t_itx;

typedef struct s_intersection_group
{
	t_itx	arr[200];
	int		count;
}	t_itx_grp;

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	double		fov;
	t_mat4s		inv_transform;
	t_mat4s		rot;
	t_vec4s		trans;
	t_vec4s		scale;
	double		half_width;
	double		half_height;
	double		half_view;
	double		aspect_ratio;
	double		pixel_size;
}	t_cam;

typedef struct s_light
{
	int		type;
	t_vec4s	pos;
	t_color	color;
	union u_light_type
	{
		struct s_point
		{
			t_color	intensity;
		};
		struct s_spot
		{
			double	intensity;
		};
	}	specs;
}	t_light;

typedef struct s_world
{
	int		num_obj;
	int		num_lights;
	t_obj	objects[100];
}	t_world;

#endif // !COMMON_H