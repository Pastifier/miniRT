/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:39:25 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 13:16:20 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vectors.h"
# include <stdint.h>

typedef struct s_object		t_object;
typedef struct s_program	t_program;

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	dir;
}	t_ray;

t_vector3	vec3_at_tip(t_ray ray, double t);

/*--- Coloring ---*/

uint32_t	ray_color(t_ray ray, t_program *context);
double		hit_sphere(t_object *obj, double ray_tmin, double ray_tmax, t_ray *ray);

#endif // !RAY_H
