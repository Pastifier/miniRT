/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:35:58 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/07 00:03:46 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "keys.h"

int	check_mouse_clicks(int button, int x, int y, void *param)
{
	const t_camera	*cam = &((t_program *)param)->cam;
	t_world	*w = &((t_program *)param)->world;
	(void)x;(void)y;(void)param;
	if (button == MOUSE_LMB)
	{
		t_ray	r = ray_for_pixel(cam, x, y);
		t_itx_grp	xs = intersect_world(w, &r);
		t_itx		*hit = get_hit(&xs);
		if (hit)
		{
			((t_program *)param)->selected.is_cam = false;
			((t_program *)param)->selected.object = hit->object;
			//lag_vec4s_normalize(&r.dir);
			//((t_program *)param)->selected.ray_dir = r.dir;
		}
	}
	return (button);
}