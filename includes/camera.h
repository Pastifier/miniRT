/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:15 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 23:18:11 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vectors.h"

typedef struct s_camera
{
	t_vector3	center;
	double		focal_length;
	int			viewport_width;
	int			viewport_height;
	t_vector3	viewport_u;
	t_vector3	viewport_v;
	t_vector3	pixel_delta_u;
	t_vector3	pixel_delta_v;
	t_vector3	cartesian_upper_left;
	t_vector3	cartesian_shift;
}	t_camera;

void	init_camera(t_camera *camera);

#endif // !CAMERA_H