/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:59:28 by ebinjama          #+#    #+#             */
/*   Updated: 2023/11/08 14:02:35 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t sz)
{
	size_t	null_dst;
	size_t	src_location;

	if (!dst && !sz)
		return (0);
	if (sz <= ft_strlen(dst))
		return (sz + ft_strlen(src));
	null_dst = ft_strlen(dst);
	src_location = 0;
	while (src[src_location] && (null_dst + 1) < sz)
	{
		dst[null_dst] = src[src_location];
		null_dst++;
		src_location++;
	}
	dst[null_dst] = 0;
	return (ft_strlen(dst) + ft_strlen(&src[src_location]));
}
