/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:25:14 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/09 04:04:30 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_atof(char **rep, float *sign, t_program *f);
static void	validate_rep(char *rep, t_program *context);
static void	validate_float(float num, t_program *f);

float	ft_atof(char *rep, t_program *context)
{
	float	mantissa;
	float	dividend;
	bool	found_point;

	validate_rep(rep, context);
	mantissa = 0.0;
	dividend = 1.0;
	found_point = false;
	init_atof(&rep, &dividend, context);
	while (*rep && ++context->flt_operations)
	{
		if (ft_isdigit(*rep)/* && ++context->flt_operations*/)
		{
			mantissa = (10 * mantissa) + (*rep - '0');
			if (found_point)
				dividend *= 10;
		}
		else if (*rep == '.' && !found_point/* && ++context->flt_operations*/)
			found_point = true;
		else
			break ;
		++rep;
	}
	validate_float(mantissa / dividend, context);
	return (mantissa / dividend);
}

static void	init_atof(char **rep, float *sign, t_program *f)
{
	f->flt_operations = 0;
	f->runtime_error = 0;
	while (**rep && (**rep == ' ' || **rep == '\t'))
		(*rep)++;
	*sign = 1.0;
	if (**rep == '-' || **rep == '+')
	{
		if (**rep == '-')
			*sign = -1.0;
		(*rep)++;
		if (!ft_isdigit(**rep))
			return (f->runtime_error = 2, (void)free(NULL));
	}
	else if (ft_isdigit(**rep))
	{
		if (*(*rep + 1) == '.')
		{
			if (!ft_isdigit(*(*rep + 2)))
				return (f->runtime_error = 2, (void)free(NULL));
		}
		else if (!ft_isdigit(*(*rep + 1)) && (*(*rep + 1)))
			return (f->runtime_error = 2, (void)free(NULL));
	}
	else
		return (f->runtime_error = 2, (void)free(NULL));
}

static void	validate_rep(char *rep, t_program *context)
{
	t_vatof	utils;

	if (!rep || (rep && !*rep))
		return (context->runtime_error = 2, (void)free(NULL));
	utils = (t_vatof){0};
	while (*rep == ' ' || *rep == '\t')
		++rep;
	while (*rep)
	{
		if (*rep == '-' || *rep == '+')
			++utils.sign_count;
		else if (ft_isdigit(*rep))
			++utils.digit_count;
		else if (*rep == '.')
			++utils.dot_count;
		else if (ft_isalpha(*rep))
			utils.found_alpha = true;
		++rep;
	}
	if (!utils.digit_count || utils.sign_count > 1 || utils.found_alpha
		|| utils.dot_count > 1)
		return (context->runtime_error = 2, (void)free(NULL));
}

static void	validate_float(float num, t_program *f)
{
	if (isnan(num) || isinf(num))
		return (f->runtime_error = 2, (void)free(NULL));
}
