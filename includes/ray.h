/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:39:25 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 12:54:16 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vectors.h"

typedef struct s_ray
{
	t_vector3 origin;
	t_vector3 dir;	
}	t_ray;

t_vector3 vec3_at_tip(t_ray ray, double t);

#endif // !RAY_H