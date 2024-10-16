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

typedef struct s_program
{
	int			runtime_error;
	int			flt_operations;
	void		*mlx;
	void		*win;
	t_canvas	canvas;
	t_world		world;
	t_camera	cam;
	struct s_ambient
	{
		bool	is_set;
		int		line_set;
		t_color	color;
		float	ratio;
	}	ambiance;
}	t_program;

typedef struct s_thread_data
{
	int			id;
	pthread_t	thread;
	t_program	*context;
	int			y;
	int			y_f;
	int			x;
	int			x_f;
}	t_thread;

/*--- PARSING ---*/

typedef struct s_validate_atof
{
	size_t	sign_count;
	size_t	dot_count;
	size_t	digit_count;
	bool	found_alpha;
}	t_vatof;

float		ft_atof(char *rep, t_program *context);
bool		parse_file(const char *filename, t_program *context);
bool		parse_ambient(t_program *context, t_split *fields, int curr_line);
bool		parse_light(t_program *context, t_split *fields, int curr_line);
bool		parse_camera(t_program *context, t_split *fields, int curr_line);

/*--- RENDERING ---*/

t_color		rt_render_pixel(t_program *context, int x, int y);
bool		create_canvas(t_program *context, int width, int height);
void		put_pixel(t_canvas *canvas, int x, int y, const t_color *color);
void		render_frame(t_program *current_context);

/*---- THREADS ----*/

void		interpolate_horizontal(t_thread const *data);
void		interpolate_vertical(t_thread const *data);
t_color		lerp_colors(const t_color *a, const t_color *b, float t);

/*--- DESTROY ---*/

void		destroy_mlx(t_program *context);
void		destroy_world(t_program *context);
void		str_arr_destroy(char **arr);

#endif // !MINIRT_H
