/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:29 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/30 12:02:36 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_vec4(t_vec4s *vec, char *str, t_program *context, int curr_line)
{
	t_split	split;

	split = ft_split(str, ",");
	if (split.wordcount != 3)
	{
		ft_putstr_fd("Error: Invalid format for Vector4 on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(": ", 2);
		ft_putendl_fd(str, 2);
		return (false);
	}
	vec->x = ft_atof(split.array[0], context);
	vec->y = ft_atof(split.array[1], context);
	vec->z = ft_atof(split.array[2], context);
	vec->w = 1.0f;
	str_arr_destroy(split.array);
	return (true);
}

bool	parse_color(t_color *color, char *str, t_program *context, int curr_line)
{
	t_split	split;

	split = ft_split(str, ",");
	if (split.wordcount != 3)
	{
		ft_putstr_fd("Error: Invalid format for Color on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(": ", 2);
		ft_putendl_fd(str, 2);
		return (false);
	}
	color->r = ft_atof(split.array[0], context);
	color->g = ft_atof(split.array[1], context);
	color->b = ft_atof(split.array[2], context);
	if (color->r < 0.0f || color->g < 0.0f || color->b < 0.0f ||
		color->r > 255.0f || color->g > 255.0f || color->b > 255.0f)
	{
		ft_putstr_fd("Error: Color values must be between 0 and 255 on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(": ", 2);
		ft_putendl_fd(str, 2);
		return (false);
	}
	color->a = 1.0f;
	str_arr_destroy(split.array);
	return (true);
}
