/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:27:30 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/06 17:29:32 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include <stdint.h> // for uint32_t

typedef struct s_canvas
{
	void	*ptr;
	char	addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_canvas;

uint32_t	get_color()

#endif // !CANVAS_H