/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:00:49 by ebinjama          #+#    #+#             */
/*   Updated: 2023/11/08 13:33:57 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t haylen)
{
	size_t	needle_len;

	if (!haylen && !haystack)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (!(needle[0]))
		return ((char *)haystack);
	while (*haystack && haylen >= needle_len)
	{
		if (*haystack == *needle && !(ft_strncmp(haystack, needle, needle_len)))
			return ((char *)haystack);
		haystack++;
		haylen--;
	}
	return (NULL);
}
