/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:36:32 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/18 15:55:45 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

void	parse_syn_err_msg(char *msg, int curr_line)
{
	ft_putstr_fd("Syntax error near unexpected token: `", STDERR_FILENO);
	ft_putchar_fd(*msg, STDERR_FILENO);
	ft_putstr_fd("` in line: ", STDERR_FILENO);
	ft_putnbr_fd(curr_line, STDERR_FILENO);
	ft_putendl_fd(".", STDERR_FILENO);
}

void	parse_err_msg(char *msg, char *expected, int curr_line)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" on line ", 2);
	ft_putnbr_fd(curr_line, 2);
	ft_putstr_fd(":\n\t", 2);
	ft_putendl_fd(expected, 2);
}

void	parse_fatal_msg(char *msg, int curr_line)
{
	ft_putstr_fd("FATAL: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" on line ", 2);
	ft_putnbr_fd(curr_line, 2);
	ft_putstr_fd(":\n\t", 2);
	ft_putendl_fd("Aborting...", 2);
}

void	parse_warn_msg(char *msg, char *expected, int curr_line, bool ign)
{
	ft_putstr_fd("Warning: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" on line ", 2);
	ft_putnbr_fd(curr_line, 2);
	if (expected)
	{
		ft_putstr_fd(":\n\t", 2);
		ft_putstr_fd(expected, 2);
	}
	if (ign)
	{
		ft_putstr_fd(":\n\t", 2);
		ft_putendl_fd("Ignoring line...", 2);
	}
}

bool	check_object_validity_init(t_program *context, const char *info,
			int curr_line, const t_split fields)
{
	if (*info == 's' && *(info + 1) == 'p')
		return (parse_sphere(context, &fields, curr_line));
	else if (*info == 'c' && *(info + 1) == 'y')
		return (parse_cylinder(context, &fields, curr_line));
	else if (*info == 'p' && *(info + 1) == 'l')
		return (parse_plane(context, &fields, curr_line));
	else if (*info == 'c' && *(info + 1) == 'u')
		return (parse_cube(context, &fields, curr_line));
	else if (*info == 'c' && *(info + 1) == 'o')
		return (parse_cone(context, &fields, curr_line));
	else if (*info == 'S' && *(info + 1) == 'L')
		return (parse_spot_light(context, &fields, curr_line));
	ft_fprintf(2, "Error: couldn't recognize object in line %d:\n", curr_line);
	return (str_arr_destroy(fields.array), false);
}
