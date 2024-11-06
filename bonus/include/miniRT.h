/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:35:52 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/16 13:18:51 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "lag.h"
# include "common.h"
# include <pthread.h>
# include <stdint.h> // for `uint32_t`
# include "libft.h" // for `t_split`
# include <stdio.h> //// TEMP
# include <sys/time.h>

# ifdef EPSILON
#  undef EPSILON
#  define EPSILON 0.0001f
# endif // !EPSILON

long long	my_gettime(void);

typedef struct s_canvas
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		bpp_8;
	int		line_length;
	int		endian;
}	t_canvas;

typedef struct s_thread_data	t_thread;

typedef struct s_program
{
	int			runtime_error;
	int			flt_operations;
	void		*mlx;
	void		*win;
	t_canvas	canvas;
	t_world		world;
	t_camera	cam;
	t_thread	*pool;
	struct s_ambient
	{
		bool	is_set;
		int		line_set;
		t_color	color;
		float	ratio;
	}	ambiance;
	bool		stop;
	struct
	{
		bool		w;
		bool		a;
		bool		s;
		bool		d;
		bool		up;
		bool		down;
		bool		left;
		bool		right;
		bool		space;
		bool		lctrl;
	}	movement;
}	t_program;

struct s_thread_data
{
	int			id;
	pthread_t	thread;
	t_program	*context;
	int			y;
	int			y_f;
	int			x;
	int			x_f;
};

typedef struct	itx_computation
{
	bool		shadowed;
	double		t;
	t_obj		*obj;
	t_vec4s		p;
	t_vec4s		over_point;
	t_vec4s		under_point;
	t_vec4s		eyev;
	t_vec4s		normalv;
	t_vec4s		reflectv;
	int			inside;
	double		n1;
	double		n2;
}	t_itx_computation;

typedef t_itx_computation t_comps;

/*--- PARSING ---*/

typedef struct s_validate_atof
{
	size_t	sign_count;
	size_t	dot_count;
	size_t	digit_count;
	bool	found_alpha;
}	t_vatof;

bool		is_normalised(t_vec4s vec);
float		ft_atof(char *rep, t_program *context);
bool		parse_file(const char *filename, t_program *context);
bool		parse_ambient(t_program *context, t_split *fields, int curr_line);
bool		parse_light(t_program *context, const t_split *fields, int curr_line);
bool		parse_camera(t_program *context, const t_split *fields, int curr_line);
bool		parse_sphere(t_program *context, const t_split *fields, int curr_line);
bool		parse_plane(t_program *context, const t_split *fields, int curr_line);
bool		parse_cube(t_program *context, const t_split *fields, int curr_line);
bool		parse_cylinder(t_program *context, const t_split *fields, int curr_line);
bool		parse_cone(t_program *context, const t_split *fields, int curr_line);
bool		parse_color(t_color *color, char *str, int curr_line);
bool		parse_vec4(t_vec4s *vec, char *str, t_program *context, int curr_line);
bool		parse_single_f(float *f, char *str, t_program *context, int curr_line);
t_mat4s		rt_extract_rot_vertical(const t_vec4s u);
t_mat4s		rt_get_cam_inverse(const t_mat4s *view);

void		parse_fatal_msg(char *msg, int curr_line);
void		parse_warn_msg(char *msg, int curr_line, bool ign);
void		parse_err_msg(char *msg, char *expected, int curr_line);

/*--- RENDERING ---*/

t_color		rt_render_pixel(t_program *context, int x, int y);
bool		create_canvas(t_program *context, int width, int height);
void		put_pixel(t_canvas *canvas, int x, int y, const t_color *color);
void		render_frame(t_program *current_context);
t_color		color_at(t_world *w, t_ray *r, int depth);

/*---- THREADS ----*/

bool		pool_init_join(t_program *context);
void		interpolate_horizontal(t_thread const *data);
void		interpolate_vertical(t_thread const *data);
t_color		lerp_colors(const t_color *a, const t_color *b, float t);

/*--- STATE ---*/

//void		update_camera_state(t_camera *camera);
int			update(void *context);
int			check_state(void *context);
int			check_key_presses(int keysym, void *context);
int			check_key_releases(int keysym, void *param);

/*--- DESTROY ---*/

void		destroy_mlx(t_program *context);
void		destroy_world(t_program *context);
int			destroy_program(t_program *context);
void		str_arr_destroy(char **arr);

/*--- RAY - MANIPULATION ---*/

void		ray_create(t_ray *ray, t_vec4s *origin, t_vec4s *direction);
void		ray_position(t_vec4s *result, const t_ray *ray, float t);
void		ray_transform(t_ray *ray, const t_mat4s *matrix);
t_vec4s		reflect(t_vec4s *in, t_vec4s *normal);

/*--- FRAGMENT CALCULATION ---*/

t_itx_grp	intersect_world(t_world *w, t_ray *r);
void		intersect_sphere(t_ray *r, t_obj *sphere, t_itx_grp *xs);
void		intersect_plane(t_ray *ray, t_obj *plane, t_itx_grp *xs);
void 		intersect_cylinder(t_ray *ray, t_obj *cy, t_itx_grp *xs);
void		intersect_cube(t_ray *ray, t_obj *cube, t_itx_grp *xs);
void		intersect_cone(t_ray *ray, t_obj *cone, t_itx_grp *xs);
t_vec4s		cone_normal_at(t_obj *cone, t_vec4s *world_point);
t_vec4s		cube_normal_at(t_obj *cube, t_vec4s *world_point);
t_vec4s 	cylinder_normal_at(t_obj *cylinder, t_vec4s *world_point);
t_vec4s		plane_normal_at(t_obj *plane);
t_vec4s		sphere_normal_at(t_obj *sphere, t_vec4s *world_p);
void		quick_sort_intersections(t_itx *arr, size_t size);
t_itx		*get_hit(t_itx_grp *xs);
void		lag_mat4s_transpose(const t_mat4s *m, t_mat4s *out);

/*--- LIGHTING ---*/

t_color	shade_hit(t_world *world, t_itx_computation *comps, int depth);
void	prepare_refractions(t_itx *hit, t_itx_computation *comps, t_itx_grp *itxs);
t_color	refracted_color(t_world *world, t_itx_computation *comps, int depth);
double	schlick(t_itx_computation *comps);

#endif // !MINIRT_H
