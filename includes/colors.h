/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:37:56 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 02:20:19 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "linear_algebra.h"

void		color(t_color *target, double r, double g, double b);
void		cadd(t_color *target, t_color *c1, t_color *c2);
void		csub(t_color *target, t_color *c1, t_color *c2);
void		cblend(t_color *target, t_color *c1, t_color *c2);
void		cscale(t_color *target, t_color *c, double scalar);
uint32_t	get_color(t_color *color);

#endif // !COLORS_H