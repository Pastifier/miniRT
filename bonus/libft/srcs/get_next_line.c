/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:22:33 by ebinjama          #+#    #+#             */
/*   Updated: 2024/02/06 10:09:50 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static t_gnl	read_till_done(int fd, char *trail);
static char		*read_to_buff(int fd, char *self, char *trail, ssize_t *fetch);
static t_gnl	extract_line(char **from, char *trail);

t_gnl	get_next_line(int fd)
{
	static char	trail[1024][BUFFER_SIZE + 1U];
	t_gnl		line;
	t_gnl		hold;

	line = (t_gnl){0};
	hold = (t_gnl){0};
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (line.error = true, line);
	trail[fd][BUFFER_SIZE] = 0;
	hold = read_till_done(fd, trail[fd]);
	if (hold.error)
		return (hold);
	if (!hold.line)
		return (hold);
	line = extract_line(&hold.line, trail[fd]);
	free(hold.line);
	return (line);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	if (!dst || !src)
		return (NULL);
	while (*src && n--)
		*dst++ = *src++;
	if (n)
		while (n--)
			*dst++ = 0;
	*dst = 0;
	return (dst);
}

char	*read_to_buff(int fd, char *self, char *trail, ssize_t *fetch)
{
	char	*temp;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (*fetch > 0 && !ft_strchr(self, '\n'))
	{
		*fetch = read(fd, trail, BUFFER_SIZE);
		if (*fetch == 0)
			return (self);
		if (*fetch < 0)
		{
			ft_memset(trail, 0, BUFFER_SIZE);
			return (free(self), NULL);
		}
		trail[*fetch] = 0;
		temp = self;
		self = ft_strjoin(self, trail);
		free(temp);
	}
	return (self);
}

t_gnl	read_till_done(int fd, char *trail)
{
	t_gnl	self;
	ssize_t	fetch;

	self = (t_gnl){0};
	if (*trail)
		self.line = ft_strdup(trail);
	fetch = 1;
	self.line = read_to_buff(fd, self.line, trail, &fetch);
	if (fetch == 0)
		self.eof = true;
	if (fetch < 0)
		self.error = true;
	return (self);
}

// TODO:
// decide how you want to deal with extracting the line
// (the trick you have in mind is using nl_address as a "bool").
//
// burn Norminette.
t_gnl	extract_line(char **from, char *trails)
{
	t_gnl	self;
	size_t	len;
	char	*nl_address;

	self = (t_gnl){0};
	nl_address = ft_strchr(*from, '\n');
	if (nl_address)
		self.len = (size_t)(nl_address - *from + 1);
	else
		self.len = ft_strlen(*from);
	len = self.len;
	self.line = malloc(sizeof(char) * (len + 1));
	if (!self.line)
		return (self.error = true, self);
	self.line[len] = 0;
	while (len--)
		self.line[len] = (*from)[len];
	if (nl_address && *(nl_address + 1))
		ft_strncpy(trails, nl_address + 1, BUFFER_SIZE);
	else
		ft_memset(trails, 0, BUFFER_SIZE);
	if (nl_address)
		return (self.len -= 1, self);
	return (self);
}
