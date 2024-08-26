/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:38:31 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 11:47:54 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "libft.h"

void	write_error(const char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putendl_fd((char *)msg, 2);
	ft_putstr_fd(DFLT, 2);
}
