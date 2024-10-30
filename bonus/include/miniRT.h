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

# include "../LagAMat/include/lag.h"
# include "common.h"
# include <pthread.h>
# include <stdint.h> // for `uint32_t`
# include "libft.h" // for `t_split`

# ifdef EPSILON
#  undef EPSILON
#  define EPSILON 0.0001
# endif // !EPSILON

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
bool		parse_color(t_color *color, char *str, t_program *context, int curr_line);
bool		parse_vec4(t_vec4s *vec, char *str, t_program *context, int curr_line);
bool		parse_single_f(float *f, char *str, t_program *context, int curr_line);
t_mat4s		rt_extract_rot_vertical(const t_vec4s u);

void		parse_fatal_msg(char *msg, int curr_line);
void		parse_warn_msg(char *msg, int curr_line);
void		parse_err_msg(char *msg, char *expected, int curr_line);

/*--- RENDERING ---*/

t_color		rt_render_pixel(t_program *context, int x, int y);
bool		create_canvas(t_program *context, int width, int height);
void		put_pixel(t_canvas *canvas, int x, int y, const t_color *color);
void		render_frame(t_program *current_context);

/*---- THREADS ----*/

bool		pool_init_join(t_program *context);
void		interpolate_horizontal(t_thread const *data);
void		interpolate_vertical(t_thread const *data);
t_color		lerp_colors(const t_color *a, const t_color *b, float t);

/*--- DESTROY ---*/

void		destroy_mlx(t_program *context);
void		destroy_world(t_program *context);
void		str_arr_destroy(char **arr);

/*--- RAY - MANIPULATION ---*/

void		ray_create(t_ray *ray, t_vec4s *origin, t_vec4s *direction);
void		ray_position(t_vec4s *result, const t_ray *ray, float t);
void		ray_transform(t_ray *ray, const t_mat4s *matrix);

/*--- FRAGMENT CALCULATION ---*/

t_itx_grp	intersect_world(t_world *w, t_ray *r);
void		intersect_sphere(t_ray *r, t_obj *sphere, t_itx_grp *xs);
t_vec4s		sphere_normal_at(t_obj *sphere, t_vec4s *world_p);
void		quick_sort_intersections(t_itx *arr, size_t size);
t_itx		*get_hit(t_itx_grp *xs);

#endif // !MINIRT_H
