/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:29 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/21 15:18:30 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

t_vec4s	*parse_vec4(char *str, t_program *context, int curr_line)
{
	t_vec4s	*vec;
	t_split	split;

	split = ft_split(str, ",");
	vec = NULL;
	if (split.wordcount != 3)
	{
		ft_putstr_fd("Error: Invalid format for Vector4 on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(": ", 2);
		ft_putendl_fd(str, 2);
		return (NULL);
	}
	vec->x = ft_atof(split.array[0], context);
	vec->y = ft_atof(split.array[1], context);
	vec->z = ft_atof(split.array[2], context);
	vec->w = 1.0f;
	str_arr_destroy(split.array);
	return (vec);
}

t_color	*parse_color(char *str, t_program *context, int curr_line)
{
	t_color	*color;
	t_split	split;

	split = ft_split(str, ",");
	color = NULL;
	if (split.wordcount != 3)
	{
		ft_putstr_fd("Error: Invalid format for Color on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(": ", 2);
		ft_putendl_fd(str, 2);
		return (str_arr_destroy(split.array), NULL);
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
		return (str_arr_destroy(split.array), NULL);
	}
	color->a = 1.0f;
	str_arr_destroy(split.array);
	return (color);
}
