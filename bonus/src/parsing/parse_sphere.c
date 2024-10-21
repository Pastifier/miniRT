/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:14:10 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/21 14:15:57 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_sphere(t_program *context, t_split *fields, int curr_line)
{
	t_obj	sp;
	t_vec4s	*vec;
	t_color	*c;

	if (fields->wordcount != 4)
	{
		ft_putstr_fd("Error: Invalid format for Sphere Object on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tSP <x>,<y>,<z> <diameter> <color>", 2);
		return (str_arr_destroy(fields->array), false);
	}

	sp.type = SPHERE;
	vec = parse_vec4(fields->array[1], context, curr_line);
	if (!vec)
		return (str_arr_destroy(fields->array), false);
	sp.trans = *vec;
	sp.specs.radius = ft_atof(fields->array[2], context) / 2.0f;
	c = parse_color(fields->array[3], context, curr_line);
	if (!c)
		return (str_arr_destroy(fields->array), false);
	sp.color = *c;
	return (true);
}
