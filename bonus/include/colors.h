/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:36:29 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 02:30:47 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "common.h"
# include <stdint.h> // for uint32_t

void		color_init(t_color *target, float r, float g, float b);
void		color_add(t_color *target, const t_color *c1, const t_color *c2);
void		color_sub(t_color *target, const t_color *c1, const t_color *c2);
void		color_blend(t_color *target, const t_color *c1, const t_color *c2);
void		color_scaleby(t_color *target, const t_color *c2, float scalar);
void		color_clamp(t_color *color);
uint32_t	get_color32(const t_color *color);

#endif // !COLORS_H
