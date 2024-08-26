/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:42:56 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 12:58:25 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

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
	t_data		img;
}	t_program;

void	init_program(int argc, char **v, t_program *program);

#endif // !__MINIRT_H