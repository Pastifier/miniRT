/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:32:19 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/07 13:0ft_strlen(field):49 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static bool	parse_optional_trails(char *field, char *value, t_material *obj_material, t_program *context)
{
	float temp;

	temp = ft_atof(value, context);
	if (!ft_strncmp(field, "reflective", ft_strlen(field)) && temp >= 0.f && temp <= 1.f)
		obj_material->reflective = temp;
	else if (!ft_strncmp(field, "transparency", ft_strlen(field)) && temp >= 0.f && temp <= 1.f)
		obj_material->transparency = temp;
	else if (!ft_strncmp(field, "refractive_index", ft_strlen(field)) && temp >= 0.f && temp <= 1.f)
		obj_material->refractive_index = temp;
	else
		return (false);
	if (context->runtime_error == 2 || context->flt_operations == 0)
		return (false);
	return (true);
}

static bool	parse_mandatory_traits(char *field, char *value, t_material *obj_material, t_program *context)
{
	float temp;

	temp = ft_atof(value, context);
	if (!ft_strncmp(field, "ambient", ft_strlen(field)) && temp >= 0.f && temp <= 1.f)
		obj_material->ambient = temp;
	else if (!ft_strncmp(field, "specular", ft_strlen(field)) && temp >= 0.f && temp <= 1.f)
		obj_material->specular = temp;
	else if (!ft_strncmp(field, "diffuse", ft_strlen(field)) && temp >= 0.f && temp <= 1.f)
		obj_material->diffuse = temp;
	else if (!ft_strncmp(field, "sheen", ft_strlen(field)) && temp >= 0.f && temp <= 200.f)
		obj_material->sheen = temp;
	else
		return (false);
	if (context->runtime_error == 2 || context->flt_operations == 0)
		return (false);
	return (true);
}

static bool	check_material_fields(t_material *obj_material, char *material_field, t_program *context, int line)
{
	t_split	split;
	bool	ret;

	split = ft_split(material_field, "=");
	if (split.wordcount != 2)
		return (parse_err_msg(ERR_M_FORMAT, ERR_EXPECT_M, line), false);
	ret = parse_mandatory_traits(split.array[0], split.array[1], obj_material, context);
	if (!ret && context->runtime_error == 2)
		return (parse_err_msg(ERR_M_VALUE, ERR_EXPECT_FLOAT, line), false);
	else if (!ret)
		return (parse_err_msg(ERR_M_FORMAT, ERR_EXPECT_M_TRAIT, line), false);
	ret = parse_optional_trails(split.array[0], split.array[1], obj_material, context);
	if (!ret && context->runtime_error == 2)
		return (parse_err_msg(ERR_M_VALUE, ERR_EXPECT_FLOAT, line), false);
	else if (!ret)
		return (parse_err_msg(ERR_M_FORMAT, ERR_EXPECT_M_OPTIONAL_TRAIT, line), false);
	return (true);
}

bool	parse_material(t_material *obj_material, char **material_fields, t_program *context, int line)
{
	t_split	traits;
	t_split	split;
	size_t	i;

	if (!material_fields || !material_fields[0] || ft_strncmp(material_fields[0], "M", 1))
		return (false);
	split = ft_split(material_fields[1], ",\n\r");
	if (split.wordcount > 7)
		return (parse_err_msg(ERR_M_FORMAT, ERR_EXPECT_M, line), false);
	i = 0;
	traits = ft_split(material_fields[1], ",");
	while (i < traits.wordcount)
	{
		if (!check_material_fields(obj_material, traits.array[i], context, line))
			parse_warn_msg("Error:\n\tInvalid material field", line, true);
		i++;
	}
	return (true);
}
