/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:38:02 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/12 19:58:17 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "render.h"

t_color	ambient_component(t_program *context, t_color obj_color)
{
	t_color	ret;

	ret = (t_color){0};
	cscale(&ret, &context->ambient.color, context->ambient.intensity);
	cblend(&ret, &ret, &obj_color);
	return (ret);
}

t_color	specular_component(t_double4 reflectv, t_comps *comps, t_light *slight,
			t_intersection *itx)
{
	t_color	ret;
	double	reflect_dot_eye;
	double	factor;

	ret = (t_color){0};
	reflect_dot_eye = vdot(&reflectv, &comps->eyev);
	if (reflect_dot_eye <= 0)
		return (ret);
	factor = itx->object->material.specular
		* pow(reflect_dot_eye, itx->object->material.shininess)
		* slight->type.spot.intensity;
	cscale(&ret, &slight->color, factor);
	return (ret);
}
