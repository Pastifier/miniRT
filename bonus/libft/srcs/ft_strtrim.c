/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:01:02 by ebinjama          #+#    #+#             */
/*   Updated: 2023/11/09 06:48:15 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks whether the character `c` is a
// member of the string `set`.
static bool	in_set(char c, const char *set);

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*self;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && in_set(s1[end - 1], set))
		end--;
	self = malloc(sizeof(char) * (end - start + 1));
	if (!self)
		return (NULL);
	i = 0;
	while (start < end)
		self[i++] = s1[start++];
	self[i] = 0;
	return (self);
}

bool	in_set(char c, const char *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (true);
	}
	return (false);
}
