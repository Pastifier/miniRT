/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:31:40 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/22 12:34:05 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

//write str
int	ft_putstr(char *str, int fd)
{
	int		count;
	int		result;

	count = 0;
	result = 0;
	if (!str)
	{
		if (write (fd, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	else
	{
		while (str[count])
		{
			if (write(fd, &str[count], 1) < 0)
				return (-1);
			else
				result++;
			count++;
		}
	}
	return (result);
}

int	ft_putstr_rev(char *str, int len, int fd)
{
	int		result;

	result = 0;
	if (!str)
		return (-1);
	else
	{
		while (str[--len])
			if (str[len] != '0')
				break ;
		while (len >= 0)
		{
			if (write(fd, &str[len], 1) < 0)
			{
				free(str);
				return (-1);
			}
			else
				result++;
			len--;
		}
	}
	free(str);
	return (result);
}

int	ft_putnbr_hex(unsigned int nbr, int mode, int fd)
{
	size_t	len;

	len = get_num_len(nbr);
	if (!mode)
		return (putnbr_hex_low(nbr, len, fd));
	else
		return (putnbr_hex_upper(nbr, len, fd));
}

int	ft_putptr(void *ptr, int fd)
{
	size_t	len;

	len = sizeof(ptr);
	if (!ptr)
	{
		if (write (fd, "0x0", 3) < 0)
			return (-1);
		return (3);
	}
	else
		return (putptr_hex((size_t)ptr, len, fd));
}
