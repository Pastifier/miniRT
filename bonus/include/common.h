/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:38:28 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/09 05:00:45 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "lag.h" // for t_vec4s, t_mat4s, and their funcs
# include <stdbool.h> // for `true`, `false`

enum e_object_types
{
	SPHERE,
	CYLINDER,
	PLANE,
	CUBE,
	CONE,
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
	float	ambient;
	float	diffuse;
	float	specular;
	float	sheen;
	float	reflective;
	float	transparency;
	float	refractive_index;
}	t_material;

typedef struct s_obj
{
	int			type;
	t_vec4s		center;
	t_mat4s		inv_transform;
	t_mat4s		transposed_inverse;
	t_mat4s		rot;
	t_vec4s		trans;
	t_vec4s		scale;
	t_vec4s		orientation;
	t_material	material;
	union u_specs
	{
		struct
		{
			float	radius;
		};
		struct
		{
			t_vec4s	normal;
		};
		struct
		{
			float	side_length;
		};
		struct
		{
			float	min;
			float	max;
			bool	closed;
		};
	}	specs;
}	t_obj;

typedef struct s_intersection
{
	float	t;
	t_obj	*object;
	//t_vec4s	itx_p;
	//// subject to be grouped somewhere else:
	//bool	shadowed;
	//t_vec4s	p;
	//t_vec4s	overp;
	//t_vec4s	underp;
	//t_vec4s	eyev;
	//t_vec4s	normalv;
	//t_vec4s	reflectv;
	//int		inside;
	float	n1;
	float	n2;
}	t_itx;

typedef struct s_intersection_group
{
	t_itx	arr[200];
	int		count;
}	t_itx_grp;

typedef struct s_ray
{
	t_vec4s		origin;
	t_vec4s		dir;
	//t_itx_grp	xs;
}	t_ray;

typedef struct s_camera
{
	bool		is_set;
	int			line_set;
	int			hsize;
	int			vsize;
	float		fov;
	t_mat4s		inv_transform;
	t_mat4s		rot;
	t_vec4s		trans;
	t_vec4s		scale; // (1, 1, 1, 1)
	float		half_width;
	float		half_height;
	float		half_view;
	float		aspect_ratio;
	float		pixel_size;
}	t_camera;

typedef struct s_light
{
	int		type;
	t_vec4s	pos;
	t_color	color;
	float	ratio;
	union u_light_type
	{
		struct s_point
		{
			t_color	intensity;
		}	point;
		struct s_spot
		{
			float	intensity;
		}	spot;
	}	specs;
}	t_light;

typedef struct s_world
{
	int		num_shapes;
	int		num_lights;
	t_obj	*shapes;
	t_light	*lights;
}	t_world;

#endif // !COMMON_H
