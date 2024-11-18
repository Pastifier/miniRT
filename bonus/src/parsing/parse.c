/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 03:10:59 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/16 13:29:29 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

static bool	read_file(int fd, t_program *context, const char *filename);
static bool	check_object_validity_and_add(t_program *context, const char *info,
				int curr_line, size_t line_len);

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
		ft_putstr_fd((char *)filename, STDERR_FILENO);
		ft_putendl_fd("` could not be opened.", STDERR_FILENO);
		return (false);
	}
	return (read_file(fd, context, filename));
}

bool	read_file_ext(t_gnl *line, t_program *context, int curr_line,
		const char *filename)
{
	if (line->error)
		return (parse_fatal_msg("Allocation failure", curr_line), false);
	if ((line->eof && curr_line == 1)
		|| (context->world.num_lights == 0 || context->world.num_shapes == 0)
		|| (!context->ambiance.is_set || !context->cam.is_set))
	{
		if (line->line)
			free(line->line);
		ft_putstr_fd("Error: file `", STDERR_FILENO);
		ft_putstr_fd((char *)filename, STDERR_FILENO);
		ft_putendl_fd("` appears to be incomplete. Need:", STDERR_FILENO);
		if (!context->world.num_lights)
			ft_putendl_fd("\tAt least one light.", 2);
		if (!context->world.num_shapes)
			ft_putendl_fd("\tAt least one shape.", 2);
		if (!context->ambiance.is_set)
			ft_putendl_fd("\tExactly one value for global Ambiance lighting.",
				2);
		if (!context->cam.is_set)
			ft_putendl_fd("\tExactly one camera.", 2);
		return (false);
	}
	return (true);
}

bool	read_file(int fd, t_program *context, const char *filename)
{
	t_gnl		line;
	uint32_t	curr_line;

	line = get_next_line(fd);
	curr_line = 1;
	while (!line.error && !line.eof)
	{
		if (*line.line == '\n' || *line.line == '#')
		{
			(free(line.line), curr_line++);
			line = get_next_line(fd);
			continue ;
		}
		if (!check_object_validity_and_add(context, line.line, curr_line++,
				line.len))
		{
			ft_putstr_fd((char *)filename, 2);
			ft_putstr_fd(":\n\t", 2);
			ft_putendl_fd(line.line, 2);
			return ((void)close(fd), free(line.line), false);
		}
		free(line.line);
		line = get_next_line(fd);
	}
	return (close(fd), read_file_ext(&line, context, curr_line, filename));
}

bool	parse_uppercase_object(t_program *context, const char *info,
			int curr_line)
{
	t_split	split;

	split = ft_split(info, " ");
	if (!split.array)
	{
		ft_putendl_fd("FATAL: Couldn't allocate for necessary operation", 2);
		return (false);
	}
	if (*info == 'A')
		return (parse_ambient(context, &split, curr_line));
	if (*info == 'C')
		return (parse_camera(context, &split, curr_line));
	if (*info == 'L')
		return (parse_light(context, &split, curr_line));
	str_arr_destroy(split.array);
	return (true);
}

bool	check_object_validity_and_add(t_program *context, const char *info,
			int curr_line, size_t line_len)
{
	const t_split	fields = ft_split(info, " ");

	if (!ft_isalpha(*info))
		return (parse_syn_err_msg((char *)info, curr_line), false);
	if (*info == 'A' || *info == 'C' || *info == 'L')
	{
		if (line_len > 1 && *(info + 1) != ' ')
			return (parse_syn_err_msg((char *)info, curr_line), false);
		return (parse_uppercase_object(context, info, curr_line));
	}
	if (*info == 's' && *(info + 1) == 'p')
		return (parse_sphere(context, &fields, curr_line));
	else if (*info == 'c' && *(info + 1) == 'y')
		return (parse_cylinder(context, &fields, curr_line));
	else if (*info == 'p' && *(info + 1) == 'l')
		return (parse_plane(context, &fields, curr_line));
	else if (*info == 'c' && *(info + 1) == 'u')
		return (parse_cube(context, &fields, curr_line));
	else if (*info == 'c' && *(info + 1) == 'o')
		return (parse_cone(context, &fields, curr_line));
	else if (*info == 'S' && *(info + 1) == 'L')
		return (parse_spot_light(context, &fields, curr_line));
	ft_fprintf(2, "Error: couldn't recognize object in line %d:\n", curr_line);
	return (false);
}
