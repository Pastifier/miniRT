/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:42:08 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 23:46:41 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

void	color(t_color *target, double r, double g, double b)
{
	target->r = r;
	target->g = g;
	target->b = b;
	point(&target->set, r, g, b);
}

void	cadd(t_color *target, t_color *c1, t_color *c2)
{
	target->r = c1->r + c2->r;
	target->g = c1->g + c2->g;
	target->b = c1->b + c2->b;
	point(&target->set, target->r, target->g, target->b);
}

void	csub(t_color *target, t_color *c1, t_color *c2)
{
	target->r = c1->r - c2->r;
	target->g = c1->g - c2->g;
	target->b = c1->b - c2->b;
	point(&target->set, target->r, target->g, target->b);
}

void	cblend(t_color *target, t_color *c1, t_color *c2)
{
	target->r = c1->r * c2->r;
	target->g = c1->g * c2->g;
	target->b = c1->b * c2->b;
	point(&target->set, target->r, target->g, target->b);
}

void	cscale(t_color *target, t_color *c, double scalar)
{
	target->r = c->r * scalar;
	target->g = c->g * scalar;
	target->b = c->b * scalar;
	point(&target->set, target->r, target->g, target->b);
}
