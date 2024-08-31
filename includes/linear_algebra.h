/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:13:57 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/31 05:39:00 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEAR_ALGEBRA_H
# define LINEAR_ALGEBRA_H

# include "rtmath.h"
# include <stdbool.h>

void		vector(t_double4 *target, double x, double y, double z);
void		point(t_double4 *target, double x, double y, double z);
t_ray		ray(t_double4 origin, t_double4 direction);

bool		d4eq(t_double4 *t1, t_double4 *t2);
void		d4add(t_double4 *target, t_double4 *t1, t_double4 *t2);
void		d4sub(t_double4 *target, t_double4 *t1, t_double4 *t2);
void		d4negate(t_double4 *target);
void		d4mul(t_double4 *target, t_double4 *t1, double scalar);
void		d4div(t_double4 *target, t_double4 *t1, double scalar);

double		vmag(t_double4 *vec);
double		vdot(t_double4 *t1, t_double4 *t2);
void		vnorm(t_double4 *target, t_double4 *t);
void		vnormalize(t_double4 *t);
void		vcross(t_double4 *target, t_double4 *t1, t_double4 *t2);


t_double4	position(t_ray *r, double t);

#endif // !LINEAR_ALGEBRA_H