/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:43:20 by ebinjama          #+#    #+#             */
/*   Updated: 2023/11/10 21:36:18 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t n)
{
	int				i;
	unsigned char	*p1_ptr;
	unsigned char	*p2_ptr;

	p1_ptr = (unsigned char *)p1;
	p2_ptr = (unsigned char *)p2;
	i = -1;
	while ((size_t)(++i) < n)
	{
		if (p1_ptr[i] != p2_ptr[i])
			return (p1_ptr[i] - p2_ptr[i]);
	}
	return (0);
}
