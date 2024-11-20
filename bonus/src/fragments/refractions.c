/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:36:36 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/20 10:25:45 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

static void	remove_from_container(t_obj **container, int *count, int i,
			t_itx_grp *itxs)
{
	int	j;

	j = 0;
	while (j < *count)
	{
		if (container[j] == itxs->arr[i].object)
		{
			while (j < *count - 1)
			{
				container[j] = container[j + 1];
				j++;
			}
			(*count)--;
			return ;
		}
		j++;
	}
}

static bool	within_container(t_obj **container, int count, int i,
			t_itx_grp *itxs)
{
	int	j;

	j = 0;
	while (j < count)
	{
		if (container[j] == itxs->arr[i].object)
			return (true);
		j++;
	}
	return (false);
}

void	prepare_refractions(t_itx *hit, t_comps *comps,
			t_itx_grp *itxs)
{
	int		count;
	int		i;
	t_obj	**container;

	container = malloc(sizeof(t_obj *) * itxs->count);
	count = 0;
	comps->n1 = 1.0;
	comps->n2 = 1.0;
	i = -1;
	while (++i < itxs->count)
	{
		if (&(itxs->arr[i]) == hit && count)
			comps->n1 = container[count - 1]->material.refractive_index;
		if (within_container(container, count, i, itxs))
			remove_from_container(container, &count, i, itxs);
		else
			container[count++] = itxs->arr[i].object;
		if (&(itxs->arr[i]) == hit)
		{
			if (count)
				comps->n2 = container[count - 1]->material.refractive_index;
			break ;
		}
	}
	free(container);
}

t_color	refracted_color(t_world *world, t_comps *comps, int depth)
{
	t_color		c;
	t_ray		r;
	float		n_ratio;
	float		cos_i;
	float		sin2_t;

	color_init(&c, 0.0, 0.0, 0.0);
	if (depth <= 0 || comps->obj->material.transparency <= 0.0)
		return (c);
	n_ratio = comps->n1 / comps->n2;
	cos_i = lag_vec4s_dot_ret(&comps->eyev, &comps->normalv);
	sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
	if (sin2_t > 1.0)
		return (c);
	lag_vec4s_scaleby(&r.dir, comps->normalv, n_ratio * cos_i
		- sqrtf(1 - sin2_t));
	lag_vec4s_scaleby(&r.origin, comps->eyev, n_ratio);
	lag_vec4s_sub(&r.dir, &r.dir, &r.origin);
	r.origin = comps->under_point;
	c = color_at(world, &r, depth - 1);
	color_scaleby(&c, &c, comps->obj->material.transparency);
	return (c);
}

//Replicates the fresnal effect by Augustin-Jean Fresnel with an accurate
//approximation. The formula is simplified to be used in ray tracing in
//order to be faster than the original formula, and not incorporate the extras
//of true Fresnel effects like light polarization.
float	schlick(t_comps *comps)
{
	float	cos;
	float	n_ratio;
	float	sin2_t;
	float	cos_t;
	float	r0;

	cos = lag_vec4s_dot_ret(&comps->eyev, &comps->normalv);
	if (comps->n1 > comps->n2)
	{
		n_ratio = comps->n1 / comps->n2;
		sin2_t = n_ratio * n_ratio * (1 - cos * cos);
		if (sin2_t > 1.0)
			return (1.0);
		cos_t = sqrtf(1.0 - sin2_t);
		cos = cos_t;
	}
	r0 = powf((comps->n1 - comps->n2) / (comps->n1 + comps->n2), 2);
	return (r0 + (1 - r0) * powf(1 - cos, 5));
}
