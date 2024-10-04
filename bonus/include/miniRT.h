/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:35:52 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/04 19:58:25 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../LagAMat/include/lag.h"
# include "common.h"
# include <pthread.h>

# ifdef EPSILON
#  undef EPSILON
#  define EPSILON 0.0001
# endif // !EPSILON

typedef struct s_canvas
{
	void	*ptr;
	char	addr;
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
	t_camera	cam;
	struct s_ambient
	{
		t_color	color;
		double	intensity;
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

#endif // !MINIRT_H