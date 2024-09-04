/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:23:51 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/04 19:40:38 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "colors.h"
# include "world.h"

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
}	t_program;

uint32_t	convert_color_uint32(t_color *color);
void		canvas(t_program *context, int width, int height);
void		put_pixel(t_canvas *canvas, int x, int y, t_color *color);

void		render(t_webcam *cam, t_world *world, t_program *context);

#endif // !RENDER_H
