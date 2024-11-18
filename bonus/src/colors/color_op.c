/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:16:04 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/18 12:16:04 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "macros.h"

void	color_add(t_color *target, const t_color *c1, const t_color *c2)
{
	float	r;
	float	b;
	float	g;

	r = c1->r + c2->r;
	g = c1->g + c2->g;
	b = c1->b + c2->b;
	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
}

void	color_sub(t_color *target, const t_color *c1, const t_color *c2)
{
	float	r;
	float	b;
	float	g;

	r = c1->r - c2->r;
	g = c1->g - c2->g;
	b = c1->b - c2->b;
	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
}

void	color_blend(t_color *target, const t_color *c1, const t_color *c2)
{
	float	r;
	float	b;
	float	g;

	r = c1->r * c2->r;
	g = c1->g * c2->g;
	b = c1->b * c2->b;
	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
}

void	color_scaleby(t_color *target, const t_color *c, float scalar)
{
	float	r;
	float	b;
	float	g;

	r = c->r * scalar;
	g = c->g * scalar;
	b = c->b * scalar;
	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
}
