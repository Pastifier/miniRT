/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:35:58 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/19 20:11:06 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "keys.h"

int	check_mouse_clicks(int button, int x, int y, void *param)
{
	const t_camera	*cam = &((t_program *)param)->cam;
	t_world			*w;
	t_ray			r;
	t_itx_grp		xs;
	t_itx			*hit;

	w = &((t_program *)param)->world;
	if (button == MOUSE_LMB)
	{
		r = ray_for_pixel(cam, x, y);
		xs = intersect_world(w, &r);
		hit = get_hit(&xs);
		if (hit)
		{
			((t_program *)param)->selected.is_cam = false;
			((t_program *)param)->selected.object = hit->object;
		}
	}
	return (button);
}
