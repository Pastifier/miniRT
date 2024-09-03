/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:37:56 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/03 13:27:29 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "linear_algebra.h"
# include "objects.h"

void		color(t_color *target, double r, double g, double b);
void		cadd(t_color *target, t_color *c1, t_color *c2);
void		csub(t_color *target, t_color *c1, t_color *c2);
void		cblend(t_color *target, t_color *c1, t_color *c2);
void		cscale(t_color *target, t_color *c, double scalar);
uint32_t	get_color(t_color *color);
t_color		color_at(t_world *w, t_ray *r);

#endif // !COLORS_H
