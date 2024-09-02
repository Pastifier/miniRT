/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 04:18:17 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/02 04:20:02 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>

# define PRINT_MATRIX(mat) \
for (int r = 0; r < 4; r++) \
{ \
	for (int c = 0; c < 4; c++) \
	{ \
		printf("%f ", mat.m[r][c]); \
	} \
	printf("\n"); \
}

# define PRINT_VECTOR(v) printf("(%0.3f, %0.3f, %0.3f, (%0.3f))\n", v.x, v.y, v.z, v.w)
# define PRINT_VECTOR_2D(v) printf("(%0.3f, %0.3f)\n", v.x, v.y);

#endif // !DEBUG_H