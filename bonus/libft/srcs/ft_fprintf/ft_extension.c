/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extension.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:28:11 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/22 12:33:50 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_conversion(char c, va_list args, int fd);
static int	check_conversion_int(char c, va_list args, int fd);

int	step_into_args(const char *str, va_list args, int fd)
{
	char	c;
	int		len;
	int		count;
	int		temp;
	int		result;

	count = 0;
	result = 0;
	temp = 0;
	len = ft_strlen(str);
	c = 0;
	while (count <= len && str[count])
	{
		c = check_next_conversion(str, count, fd);
		if (c < 0)
			return (-1);
		temp = check_conversion(c, args, fd);
		if (temp < 0)
			return (-1);
		result += temp;
		count = get_next_index(str, count);
	}
	return (get_pure_strlen(str) + result);
}

static int	check_conversion(char c, va_list args, int fd)
{
	if (c == 's')
		return (ft_putstr(va_arg(args, char *), fd));
	else if (c == 'c')
		return (ft_putchar((va_arg(args, unsigned int)), fd));
	else if (c == 'd' || c == 'i' || c == 'u')
		return (check_conversion_int(c, args, fd));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *), fd));
	else if (c == 'x')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 0, fd));
	else if (c == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 1, fd));
	else if (c == '%')
		return (write(fd, "%", 1));
	return (0);
}

static int	check_conversion_int(char c, va_list args, int fd)
{
	int		res;
	char	*str;

	if (c == 'i' || c == 'd')
	{
		str = ft_itoa(va_arg(args, int));
		if (!str)
			return (-1);
		res = ft_putstr(str, fd);
		free(str);
		return (res);
	}
	else if (c == 'u')
	{
		str = ft_unsigned_itoa(va_arg(args, unsigned int));
		if (!str)
			return (-1);
		res = ft_putstr(str, fd);
		free(str);
		return (res);
	}
	return (0);
}

int	get_num_len(unsigned int nbr)
{
	int	c;

	c = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		c++;
	}
	return (c);
}
