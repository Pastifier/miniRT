/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:02:53 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/19 15:00:23 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static bool	parse_bump_xpm(t_material *obj_mat, t_program *context,
		char *filename)
{
	t_list	*temp;

	if (ft_strlen(filename) < 5 || ft_strncmp(filename + ft_strlen(filename)
			- 4, ".xpm", 4))
		return (context->runtime_error = 3, false);
	temp = context->textures;
	while (temp && temp->content)
	{
		if (!ft_strncmp(((t_texture *)temp->content)->name,
				filename, ft_strlen(filename)))
			return (obj_mat->tex = ((t_texture *)temp->content)->tex, true);
		temp = temp->next;
	}
	temp->content = malloc(sizeof(t_texture));
	if (!temp->content)
		return (context->runtime_error = 3, false);
	((t_texture *)temp->content)->name = ft_strdup(filename);
	if (!((t_texture *)temp->content)->name)
		return (context->runtime_error = 3, false);
	((t_texture *)temp->content)->tex = rt_xpm_file_to_canvas(
			filename, context->mlx);
	obj_mat->tex = ((t_texture *)temp->content)->tex;
	if (!obj_mat->tex)
		return (context->runtime_error = 3, false);
	return (true);
}

static bool	parse_traits_extension(char *field, char *value,
	t_material *obj_material, t_program *context)
{
	float	temp;

	temp = ft_atof(value, context);
	if (!ft_strncmp(field, "reflective", ft_strlen(field)) && temp >= 0.f
		&& temp <= 1.f)
		obj_material->reflective = temp;
	else if (!ft_strncmp(field, "transparency", ft_strlen(field)) && temp
		>= 0.f && temp <= 1.f)
		obj_material->transparency = temp;
	else if (!ft_strncmp(field, "refractive_index", ft_strlen(field)) && temp
		>= 0.f && temp <= 2.f)
		obj_material->refractive_index = temp;
	else if (!ft_strncmp(field, "bump_xpm", ft_strlen(field)))
		return (parse_bump_xpm(obj_material, context, value));
	else if (!ft_strncmp(field, "checker", ft_strlen(field)))
		return (parse_plane_checker(obj_material, context, value));
	else
		return (false);
	if (context->runtime_error == 2 || context->flt_operations == 0)
		return (false);
	return (true);
}

static bool	parse_traits(char *field, char *value, t_material *obj_material,
	t_program *context)
{
	float	temp;

	temp = ft_atof(value, context);
	if (!ft_strncmp(field, "ambient", ft_strlen(field)) && temp
		>= 0.f && temp <= 1.f)
		obj_material->ambient = temp;
	else if (!ft_strncmp(field, "specular", ft_strlen(field)) && temp
		>= 0.f && temp <= 1.f)
		obj_material->specular = temp;
	else if (!ft_strncmp(field, "diffuse", ft_strlen(field)) && temp
		>= 0.f && temp <= 1.f)
		obj_material->diffuse = temp;
	else if (!ft_strncmp(field, "sheen", ft_strlen(field)) && temp
		>= 0.f && temp <= 200.f)
		obj_material->sheen = temp;
	else
		return (parse_traits_extension(field, value, obj_material, context));
	if (context->runtime_error == 2 || context->flt_operations == 0)
		return (false);
	return (true);
}

static bool	check_material_fields(t_material *obj_material,
	char *material_field, t_program *context, int line)
{
	t_split	split;
	bool	ret;

	split = ft_split(material_field, "=\n\r");
	if (split.wordcount != 2)
		return (parse_warn_msg(ERR_M_FORMAT, ERR_EXPECT_M, line, false), false);
	ret = parse_traits(split.array[0], split.array[1], obj_material, context);
	if (!ret && context->runtime_error == 3)
		return (parse_warn_msg(ERR_M_BUMP_FORMAT, ERR_EXPECT_XPM, line, true),
			true);
	else if (!ret && (context->runtime_error == 2 || context->flt_operations
			== 0))
		return (parse_warn_msg(ERR_M_VALUE, ERR_EXPECT_FLOAT, line, true),
			true);
	else if (!ret && context->runtime_error == 4)
		return (parse_warn_msg(ERR_M_CHECKER, ERR_EXPECT_CHECKER, line, true),
			true);
	else if (!ret)
		return (parse_warn_msg(ERR_M_FORMAT, ERR_EXPECT_M_TRAIT, line, true),
			true);
	return (true);
}

bool	parse_material(t_material *obj_material, char **material_fields,
	t_program *context, int line)
{
	t_split	traits;
	t_split	split;
	size_t	i;

	if (!material_fields || !material_fields[0]
		|| ft_strncmp(material_fields[0], "M", 1))
		return (false);
	split = ft_split(material_fields[1], ",\n\r");
	if (split.wordcount > 7)
		return (parse_err_msg(ERR_M_FORMAT, ERR_EXPECT_M, line), false);
	i = 0;
	traits = ft_split(material_fields[1], ",");
	while (i < traits.wordcount)
	{
		if (!check_material_fields(obj_material, traits.array[i], context,
				line))
			return (false);
		i++;
	}
	return (true);
}
