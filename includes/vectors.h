/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:46:58 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 16:53:36 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

t_vector3	vec3_subtract(t_vector3 a, t_vector3 b);
t_vector3	vec3_add(t_vector3 a, t_vector3 b);
t_vector3	vec3_scaleby(t_vector3 a, double f);
double		vec3_magnitude(t_vector3 a);
double		vec3_magnitude_sqrd(t_vector3 a);
double		vec3_dot(t_vector3 u, t_vector3 v);
t_vector3	vec3_cross(t_vector3 u, t_vector3 v);
t_vector3	vec3_normal(t_vector3 v);
void		vec3_print(t_vector3 v);

#endif // !__VECTORS_H
