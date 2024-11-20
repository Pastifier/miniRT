/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:55:36 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/19 16:11:38 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static bool	parse_new_bump_xpm(t_material *obj_mat, t_program *context,
		char *filename)
{
	t_list	*new;

	new = ft_lstnew(NULL);
	new->content = malloc(sizeof(t_texture));
	if (!new->content)
		return (free(new), context->runtime_error = 3, false);
	((t_texture *)new->content)->name = ft_strdup(filename);
	if (!((t_texture *)new->content)->name)
		return (ft_lstdelone(new, free), context->runtime_error = 3, false);
	((t_texture *)new->content)->tex = rt_xpm_file_to_canvas(
			filename, context->mlx);
	obj_mat->tex = ((t_texture *)new->content)->tex;
	if (!obj_mat->tex)
		return (free(((t_texture *)new->content)->name), ft_lstdelone(new,
				free), context->runtime_error = 3, false);
	ft_lstadd_back(&context->textures, new);
	return (true);
}

bool	parse_bump_xpm(t_material *obj_mat, t_program *context,
		char *filename)
{
	t_list	*temp;

	if (ft_strlen(filename) < 5 || ft_strncmp(filename + ft_strlen(filename)
			- 4, ".xpm", 4))
		return (context->runtime_error = 3, false);
	temp = context->textures;
	while (temp)
	{
		if (!ft_strncmp(((t_texture *)temp->content)->name,
				filename, ft_strlen(filename)))
			return (obj_mat->tex = ((t_texture *)temp->content)->tex, true);
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	return (parse_new_bump_xpm(obj_mat, context, filename));
}
