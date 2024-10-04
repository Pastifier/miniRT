/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:39:03 by ebinjama          #+#    #+#             */
/*   Updated: 2024/06/14 03:08:30 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

/*
	Returns true if a character is whitespace.
*/
static bool	is_white(int c);
static bool	init_atoi(const char *str, int *pom, t_ull *res);
static bool	is_permissible(int c);

t_eint	ft_atoi(const char *str)
{
	int		sign;
	t_ull	result;
	t_eint	self;

	self = (t_eint){0, 0, 0};
	result = 0;
	sign = 1;
	if (!init_atoi(str, &sign, &result))
		return ((t_eint){.value = result, .error = true});
	while (is_permissible(*str))
		++str;
	while (ft_isdigit(*str))
	{
		result = (result * 10) + ((char)(*str) - '0');
		self.operations += 1;
		++str;
	}
	if (self.operations < 1 || *str)
		self.error = true;
	if (result > INT_MAX + 1ULL && sign < 0)
		return ((t_eint){.value = 0, .error = true});
	else if (result > INT_MAX && sign > 0)
		return ((t_eint){.value = -1, .error = true});
	self.value = result * sign;
	return (self);
}

bool	init_atoi(const char *str, int *pom, t_ull *res)
{
	size_t	digits;

	if (!str || !(str && *str))
		return (false);
	digits = 0;
	while (is_white(*str))
		str++;
	if (*str == '-')
		*pom = -1;
	if (*str == '-' || *str == '+')
		++str;
	if (!*str || *str == '-' || *str == '+'
		|| is_white(*str))
		return (false);
	while (*str == '0')
		++str;
	--str;
	while (*++str && ft_isdigit(*str))
		++digits;
	if (digits >= 20 && *pom > 0)
		return (*res = -1, false);
	if (digits >= 20 && *pom < 0)
		return (*res = 0, false);
	return (true);
}

bool	is_white(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static bool	is_permissible(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '+' || c == '-');
}
