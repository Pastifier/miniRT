/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:23:51 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/12 19:56:52 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "colors.h"
# include "pthread.h"

typedef struct s_world t_world;
typedef struct s_camera t_camera;

typedef struct s_canvas
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_canvas;

typedef struct s_program
{
	void		*mlx;
	void		*win;
	t_canvas	canvas;
	t_world		world;
	t_camera	camera;
	struct s_ambient
	{
		t_color	color;
		double	intensity;
	}	ambient;
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
}	t_thread_data;

uint32_t	get_color(t_color *color);
t_color		render_pixel(t_program *context, int x, int y);
void		canvas(t_program *context, int width, int height);
void		put_pixel(t_canvas *canvas, int x, int y, t_color color);
void		render_clock(t_program	*context);
void		render_sphere(t_program *context);
void		render_scene(t_program *context);

t_color		super_sample_pix(t_thread_data *data, double x, double y);
void		interpolate_horizontal(t_thread_data *data);
void		interpolate_vertical(t_thread_data *data);

#endif // !RENDER_H
