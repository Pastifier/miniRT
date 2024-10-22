/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:59:52 by ebinjama          #+#    #+#             */
/*   Updated: 2023/11/09 06:32:03 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t sz)
{
	size_t	i;
	size_t	src_len;

	if (!sz)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	if (src_len > --sz)
		src_len = sz;
	i = 0;
	while (i < src_len)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}
