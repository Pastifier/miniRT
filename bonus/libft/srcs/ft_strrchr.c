/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:00:56 by ebinjama          #+#    #+#             */
/*   Updated: 2024/02/01 10:40:36 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*store;

	ptr = (char *)s;
	if (!ptr)
		return (NULL);
	store = NULL;
	while (*ptr)
	{
		if (*ptr == (char)c)
			store = ptr;
		ptr++;
	}
	if (!(char)c)
		return (ptr);
	return (store);
}
