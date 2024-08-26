/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:42:56 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 16:29:48 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vectors.h"

/*--- CONST. DEFINES ---*/

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 720
# endif // !WIN_HEIGHT

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1280
# endif // !WIN_WIDTH

/*--- 	 STRUCTS 	---*/

typedef struct s_camera
{
	t_vector3	origin;
	double	focal_length;
	double	viewport_width;
	double	viewport_height;
	t_vector3	viewport_u;
	t_vector3	viewport_v;
	t_vector3 pixel_delta_u;
	t_vector3 pixel_delta_v;
}	t_camera;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	aspect_ratio;
}			t_data;

typedef struct s_program
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_camera	camera;
}	t_program;

void	init_program(int argc, char **v, t_program *program);

#endif // !__MINIRT_H
