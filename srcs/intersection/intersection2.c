/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 07:08:11 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 05:03:54 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "linear_algebra.h"
#include "colors.h"
#include <stdio.h>

t_double4	reflect(t_double4 *in, t_double4 *s_normal)
{
	t_double4	in_minus_normal_times_2_times_their_dot;
	t_double4	normal_times_2_times_in_dot_normal;
	t_double4	normalised_in;

	vnorm(&normalised_in, in);
	d4mul(&normal_times_2_times_in_dot_normal,
		s_normal, 2.0 * vdot(&normalised_in, s_normal));
	d4sub(&in_minus_normal_times_2_times_their_dot,
		in, &normal_times_2_times_in_dot_normal);
	return (in_minus_normal_times_2_times_their_dot);
}

t_light	point_light(t_double4 *pos, t_color *intensity)
{
	return ((t_light)
	{
		.intensity = *intensity,
		.pos = *pos
	});
}

// I already added itx point to the ray. So, remember to remove it later
// and adjust the function accordingly!

t_color	lighting(t_mat *mat, t_light *light, t_double4 *pos, t_ray *r)
{
	t_color		effective_color;
	t_double4	lightv;
	t_double4	reflectv;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	double		light_dot_s_normal;
	double		reflect_dot_eye;
	double		factor;
	t_color		result;

	cblend(&effective_color, &mat->c, &light->intensity);
	d4sub(&lightv, &light->pos, pos);
	vnormalize(&lightv);
	cscale(&ambient, &effective_color, mat->amb);
	r->s_normal.w = 0;
	light_dot_s_normal = vdot(&lightv, &r->s_normal);
	if (light_dot_s_normal < 0.0)
	{
		cinit(&diffuse, 0, 0, 0);
		cinit(&specular, 0, 0, 0);
	}
	else
		cscale(&diffuse, &effective_color, mat->diff * light_dot_s_normal);
	d4negate(&lightv);
	reflectv = reflect(&lightv, &r->s_normal);
	reflect_dot_eye = vdot(&reflectv, &r->eye);
	if (reflect_dot_eye <= 0)
		cinit(&specular, 0, 0, 0);
	else
	{
		factor = pow(reflect_dot_eye, mat->shiny);
		cscale(&specular, &light->intensity, mat->spec * factor);
	}
	cadd(&result, &ambient, &diffuse);
	cadd(&result, &result, &specular);
	return (result);
}
