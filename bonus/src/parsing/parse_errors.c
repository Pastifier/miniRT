/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:36:32 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/22 13:37:11 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

void	parse_err_msg_abort(char *msg, char *expected, int curr_line)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" on line ", 2);
	ft_putnbr_fd(curr_line, 2);
	ft_putstr_fd(":\n\t", 2);
	if (expected)
		ft_putendl_fd(expected, 2);
	else
		ft_putendl_fd("Aborting...", 2);
}

void	parse_err_msg_ignore(char *msg, char *expected, int curr_line)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" on line ", 2);
	ft_putnbr_fd(curr_line, 2);
	ft_putstr_fd(":\n\t", 2);
	if (expected)
		ft_putendl_fd(expected, 2);
	else
		ft_putendl_fd("Ignoring line...", 2);
}
