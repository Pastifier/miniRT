/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:42:20 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/02 14:06:37 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat2x2	submat3x3(t_mat3x3 *m, int row, int col)
{
	static t_double3	unallowed;
	t_double3			*rows;
	t_mat2x2			res;

	res = (t_mat2x2){0};
	unallowed = row3(INFINITY, INFINITY, INFINITY);
	rows = &m->r1;
	rows[row] = unallowed;
	(void)col;
	return (res);
}
