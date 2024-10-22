/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:36:32 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/22 13:57:17 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

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

void	parse_warn_msg(char *msg, int curr_line)
{
	ft_putstr_fd("Warning: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" on line ", 2);
	ft_putnbr_fd(curr_line, 2);
	ft_putstr_fd(":\n\t", 2);
	ft_putendl_fd("Ignoring line...", 2);
}
