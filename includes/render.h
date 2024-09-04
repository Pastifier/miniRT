/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:23:51 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/04 13:00:40 by melshafi         ###   ########.fr       */
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
}	t_program;

typedef struct s_thread_data
{
	int			id;
	pthread_t	thread;
	t_program	*context;
	t_double2	start;
	t_double2	end;
}	t_thread_data;

uint32_t	get_color(t_color *color);
void		canvas(t_program *context, int width, int height);
void		put_pixel(t_canvas *canvas, int x, int y, t_color *color);
void		render_clock(t_program	*context);
void		render_sphere(t_program *context);
void		render_scene(t_program *context);

#endif // !RENDER_H
