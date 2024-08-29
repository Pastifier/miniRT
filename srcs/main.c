/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 07:40:15 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "miniRT.h"
#include "macros.h"
#include "linear_algebra.h"
#include <stdio.h>
#include "matrix.h"

#define PRINT_VECTOR(v) printf("(%0.3f, %0.3f, %0.3f)\n", v.x, v.y, v.z)

#include "mlx.h"

int main(void)
{
	t_mat4x4	m = mat4x4(
		row4(1, 2, 3, 4),
		row4(2, 4, 4, 2),
		row4(8, 6, 4, 1),
		row4(0, 0, 0, 1)
	);

	t_mat4x4	m2 = mat4x4(
		row4(1, 0, 0, 0),
		row4(0, 1, 0, 0),
		row4(0, 0, 1, 0),
		row4(0, 0, 0, 1)
	);

	t_mat4x4	m3 = mat4x4_mul(&m, &m2);

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
			printf("%0.3f ", m3.m[r][c]);
		printf("\n");
	}
	return (0);
}
