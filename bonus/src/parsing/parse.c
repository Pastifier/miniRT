/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 03:10:59 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 06:39:24 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

bool	read_file(int fd, t_program *context, const char *filename);
bool	check_object_validity_and_add(t_program *context, const char *info,
			int curr_line);

bool	parse_file(const char *filename, t_program *context)
{
	int			fd;
	const char	*extension = ft_strchr(filename, '.');

	if (!extension || (extension && ft_strncmp(extension, ".rt", 4)))
		return ((void)write(2, "FATAL: Need file of type '*.rt'\n", 33), false);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("FATAL: file `", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd("` could not be opened.", STDERR_FILENO);
		return (false);
	}
	return (read_file(fd, context, filename));
}

bool	read_file(int fd, t_program *context, const char *filename)
{
	t_gnl		line;
	uint32_t	curr_line;

	line = get_next_line(fd);
	curr_line = 1;
	while (!line.error && !line.eof)
	{
		if (*line.line == '\n')
		{
			(free(line.line), curr_line++);
			line = get_next_line(fd);
			continue ;
		}
		if (!check_object_validity_and_add(context, line.line, curr_line++))
			return ((void)close(fd), free(line.line), false);
		free(line.line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line.error)
	{
		ft_putendl_fd("FATAL: Allocation failure", STDERR_FILENO);
		return (false);
	}
	if ((line.eof && curr_line == 1)
		|| (context->world.num_lights == 0 && context->world.num_shapes == 0))
	{
		//if (line.line)
		//	free(line.line);
		ft_putstr_fd("Error: file `", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd("` appears to be empty.", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	check_object_validity_and_add(t_program *context, const char *info,
			int curr_line)
{
	(void)context;
	if (!ft_isalpha(*info))
	{
		ft_putstr_fd("Syntax error near unexpected token: `", STDERR_FILENO);
		ft_putchar_fd(*info, STDERR_FILENO);
		ft_putstr_fd("` in line: ", STDERR_FILENO);
		ft_putnbr_fd(curr_line, STDERR_FILENO);
		ft_putendl_fd(".", STDERR_FILENO);
	}
	//if (*info >= 'A' && *info <= 'Z')
	//	return (parse_uppercase_object(context, info, curr_line));
	//if (*info == 's' && *(info + 1) == 'p')
	//	return (parse_sphere(context, info, curr_line));
	//if (*info == 'c' && *(info + 1) == 'y')
	//	return (parse_cylinder(context, info, curr_line));
	//if (*info == 'p' && *(info + 1) == 'l')
	//	return (parse_plane(context, info, curr_line));
	//if (*info == 'c' && *(info + 1) == 'u')
	//	return (parse_cube(context, info, curr_line));
	//else
	//{
		ft_putstr_fd("Error: couldn't recognize object in line ", 2);
		ft_putnbr_fd(curr_line, 2);
		(ft_putstr_fd(":\n\t", 2), ft_putendl_fd(info, 2));
	//}
	return (false);
}

