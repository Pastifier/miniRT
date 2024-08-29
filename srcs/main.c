/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 10:57:08 by ebinjama         ###   ########.fr       */
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
		row4(-5, 2, 6, -8),
		row4(1, -5, 1, 8),
		row4(7, 7, -6, -7),
		row4(1, -3, 7, 4)
	);

	t_mat4x4	inv = mat4x4_inverse(&m);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
			printf("%0.5f\t", inv.m[r][c]);
		printf("\n");
	}
	return (0);
}
