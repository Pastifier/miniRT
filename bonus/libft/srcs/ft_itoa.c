/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:41:09 by ebinjama          #+#    #+#             */
/*   Updated: 2023/11/09 06:59:13 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Returns the absolute value of `nbr`.
*/
static int	absolute(int nbr);

/*
	Returns the number of digits in nbr.
*/
static int	digitnum(int nbr);

char	*ft_itoa(int n)
{
	char	*self;
	int		sign;
	size_t	digits;

	digits = digitnum(n);
	sign = (n < 0);
	self = ft_calloc(digits + sign + 1, sizeof(char));
	if (!self)
		return (NULL);
	while (digits)
	{
		if (n < 0)
			self[digits--] = '0' + absolute(n % 10);
		else
			self[--digits] = '0' + absolute(n % 10);
		n /= 10;
	}
	if (sign)
		self[0] = '-';
	return (self);
}

int	absolute(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

int	digitnum(int nbr)
{
	int	count;

	count = 0;
	if (!nbr)
		return (1);
	if (nbr == INT_MIN)
		return (10);
	while (nbr)
	{
		++count;
		nbr /= 10;
	}
	return (count);
}
