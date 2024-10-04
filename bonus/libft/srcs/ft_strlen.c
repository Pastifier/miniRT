/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:00:00 by ebinjama          #+#    #+#             */
/*   Updated: 2024/02/01 11:43:39 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		++i;
	return (i);
}

/* size_t ft_strlen(const char *str)
	{
		unsigned char	*store;
		unsigned char	*dummy;
		
		store = (unsigned char *)str;
		dummy = (unsigned char *)store;
		while (*dummy)
			dummy++;
		return ((size_t)dummy - (size_t)store);
	}
	I BET YOU'RE MAD HAHAHAHAHAH! Noob! THIS IS HOW REAL MEN DO IT!
	IN A WORLD... WHERE DECLARING COUNTERS IS FORBIDDEN...
	A SINGLE MAN PREVAILED...
	This is the story of...
	The Pointer Master
	*trailer music*
*/
