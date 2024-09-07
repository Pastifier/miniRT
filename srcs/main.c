/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/30 23:32:11y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

t_color COLOR_RED;

#include "mlx.h"

void	fill_canvas(t_canvas *canvas, uint32_t color)
{
	int	i;

	i = 0;
	while (i < canvas->line_length * WIN_HEIGHT)
	{
		*(uint32_t *)(canvas->addr + i) = color;
		i += sizeof(uint32_t);
	}
}

int main(void)
{
//// World from chapter seven
	//world_from_chapter_7();

//// Chapter 13
	//test_rays_should_miss_cylinder();
	//test_rays_should_intersect_cylinder();
	//test_normal_on_cy();
	//test_intersections_on_truncated_cy();
	//test_intersections_on_capped_cy();
	//test_normal_on_cy_caps();
	//test_render_simple_cy();
	test_render_transformed_cy();

	return (0);
}
