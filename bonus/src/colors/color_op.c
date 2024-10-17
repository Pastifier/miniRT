/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 02:17:38 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 02:26:46y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "macros.h"

void	color_add(t_color *target, const t_color *c1, const t_color *c2)
{
	const float r = c1->r + c2->r;
	const float g = c1->g + c2->g;
	const float b = c1->b + c2->b;

	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
}

void	color_sub(t_color *target, const t_color *c1, const t_color *c2)
{
	const float r = c1->r - c2->r;
	const float g = c1->g - c2->g;
	const float b = c1->b - c2->b;

	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
}

void	color_blend(t_color *target, const t_color *c1, const t_color *c2)
{
	const float r = c1->r * c2->r;
	const float g = c1->g * c2->g;
	const float b = c1->b * c2->b;

	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
}

void	color_scaleby(t_color *target, const t_color *c, float scalar)
{
	const float r = c->r * scalar;
	const float g = c->g * scalar;
	const float b = c->b * scalar;

	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
}