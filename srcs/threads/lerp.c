/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:39:10 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/09 14:45:23 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "render.h"

void	actual_interpolate_vertically(double x, double y, t_canvas *canvas,
		int threshold, t_world *w)
{
	int				c_i;
	//int				s_i; // Ratio-helper for dynamic pixel-skippage
	int				c_f;
	//int				s_f; // Will implement later
	t_intersections	xs;
	t_ray			r;

	c_i = get_pixel(canvas, x - 1, y);
	c_f = get_pixel(canvas, x + SKIPPED_PIXELS - 1, y);
	if (cdiff(c_i, c_f) <= threshold)
	{
		put_pixel(canvas, x, y, clerp(c_i, c_f, 2.0 / 3.0));
		put_pixel(canvas, x + 1, y, clerp(c_i, c_f, 1.0 / 3.0));
	}
	else
	{
		r = to_the_pixel_and_beyond(&w->cam, x, y);
		r.c = color_at(w, &r);
		put_pixel(canvas, x, y, &r.c);
	}
}