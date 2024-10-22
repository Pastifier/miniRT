/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:38:05 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/22 11:27:44 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putstr_ptr(char *str, int len, int fd);

int	putnbr_hex_low(unsigned int nbr, size_t len, int fd)
{
	char	*str;
	int		hex_pos;
	int		result;

	hex_pos = 0;
	len *= 2;
	if (nbr == 0)
		return (ft_putchar_fd('0', fd), 1);
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (-1);
	while ((size_t)hex_pos < len)
	{
		if (nbr % 16 >= 10)
			str[hex_pos] = 'a' + nbr % 16 % 10;
		else if (nbr % 16 <= 9)
			str[hex_pos] = '0' + nbr % 16;
		hex_pos++;
		nbr /= 16;
	}
	result = ft_putstr_rev(str, hex_pos, fd);
	if (result < 0)
		return (-1);
	return (result);
}

int	putnbr_hex_upper(unsigned int nbr, size_t len, int fd)
{
	char	*str;
	int		hex_pos;
	int		result;

	hex_pos = 0;
	len *= 2;
	if (nbr == 0)
		return (ft_putchar_fd('0', fd), 1);
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (-1);
	while ((size_t)hex_pos < len)
	{
		if (nbr % 16 >= 10)
			str[hex_pos] = 'A' + nbr % 16 % 10;
		else if (nbr % 16 <= 9)
			str[hex_pos] = '0' + nbr % 16;
		hex_pos++;
		nbr /= 16;
	}
	result = ft_putstr_rev(str, hex_pos, fd);
	if (result < 0)
		return (-1);
	return (result);
}

int	putptr_hex(size_t ptr, size_t len, int fd)
{
	char	*str;
	int		hex_pos;
	int		result;

	hex_pos = 0;
	len *= 2;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (-1);
	while ((size_t)hex_pos < len)
	{
		if (ptr % 16 >= 10)
			str[hex_pos] = 'a' + ptr % 16 % 10;
		else if (ptr % 16 >= 1 && ptr % 16 <= 9)
			str[hex_pos] = '0' + ptr % 16;
		hex_pos++;
		ptr /= 16;
	}
	result = ft_putstr_ptr(str, hex_pos, fd);
	if (result < 0)
		return (-1);
	return (result);
}

static int	ft_putstr_ptr(char *str, int len, int fd)
{
	int	result;
	int	temp;

	result = 0;
	temp = write(1, "0x", 2);
	while (str[len - 1] == '\0')
		len--;
	if (temp < 0)
		free(str);
	if (temp < 0)
		return (-1);
	result += 2;
	while (len-- > 0)
	{
		if (!str[len])
			str[len] = '0';
		temp = write(fd, &str[len], ft_strlen(&str[len]));
		if (temp < 0)
			free(str);
		if (temp < 0)
			return (-1);
		result += temp;
	}
	free(str);
	return (result);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	char			*str;
	unsigned int	num_len;

	num_len = get_num_len(n);
	if (n == 0)
	{
		str = ft_calloc(2, sizeof(char));
		if (!str)
			return (NULL);
		str[1] = 0;
		str[0] = '0';
		return (str);
	}
	str = ft_calloc(num_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[num_len] = 0;
	while (num_len--)
	{
		str[num_len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
