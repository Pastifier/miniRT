/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:37:56 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/09 16:40:13 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "linear_algebra.h"
# include "objects.h"

typedef struct s_canvas t_canvas;

void		color(t_color *target, double r, double g, double b);
void		cadd(t_color *target, t_color *c1, t_color *c2);
void		csub(t_color *target, t_color *c1, t_color *c2);
void		cblend(t_color *target, t_color *c1, t_color *c2);
void		cscale(t_color *target, t_color *c, double scalar);
uint32_t	get_color(t_color *color);
void		cclamp(t_color *color);
t_color		color_at(t_world *w, t_ray *r);
t_color		get_pixel_color(t_canvas *canvas, int x, int y);
t_color		lerp(t_color a, t_color b, double t);
int			cdiff(t_color a, t_color b);

#endif // !COLORS_H
