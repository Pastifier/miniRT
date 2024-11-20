/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:52:40 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/22 12:32:04 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		success;

	success = 1;
	if (!str || fd < 0)
		return (-1);
	va_start(args, str);
	success = step_into_args(str, args, fd);
	va_end (args);
	return (success);
}

char	check_next_conversion(const char *str, int count, int fd)
{
	while (str[count])
	{
		if (str[count] == '%' && str[count + 1])
		{
			if (exists_in(str[count + 1], "cspdiuxX%%"))
				return (str[count + 1]);
		}
		else
		{
			if (write(fd, &str[count], 1) < 0)
				return (-1);
		}
		count++;
	}
	return ('\0');
}

char	exists_in(char c, char *set)
{
	int	count;

	count = 0;
	while (set[count])
	{
		if (set[count] == c)
			return (c);
		count++;
	}
	return ('\0');
}

int	get_next_index(const char *str, int count)
{
	while (str[count])
	{
		if (str[count] == '%' && str[count + 1])
			if (exists_in(str[count + 1], "cspdiuxX%%"))
				return (count + 2);
		count++;
	}
	return (count + 2);
}

int	get_pure_strlen(const char *str)
{
	int	count;
	int	len;

	count = 0;
	len = 0;
	while (str[count])
	{
		if (str[count] == '%' && str[count + 1])
		{
			if (exists_in(str[count + 1], "cspdiuxX%%"))
				count += 2;
		}
		else
		{
			count++;
			len++;
		}
	}
	return (len);
}
