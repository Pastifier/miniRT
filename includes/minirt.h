/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:42:56 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 14:05:26 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "camera.h"

/*--- CONST. DEFINES ---*/

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 720
# endif // !WIN_HEIGHT

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1280
# endif // !WIN_WIDTH

# ifndef ASPECT_RATIO
#	define ASPECT_RATIO WIN_WIDTH / WIN_HEIGHT
# endif //	!ASPECT_RATIO

/*--- 	 STRUCTS 	---*/

typedef struct s_object	t_object;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_program
{
	void		*mlx;
	void		*win;
	int			num_objects;
	t_object	*objects;
	t_data		img;
	t_camera	camera;
}	t_program;

void	init_program(int argc, char **v, t_program *program);
int		move_camera(int keycode, t_program *context);

#endif // !__MINIRT_H
