/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:12:40 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/09 15:58:42 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# ifdef __MACH__
#  define OS_MACOS 1
# else
#  define OS_MACOS 0
# endif // !__MACH__

# ifndef THRESHOLD
#  define THRESHOLD 25
# endif // !THRESHOLD

# ifndef REFLECTION_DEPTH
#  define REFLECTION_DEPTH 5
# endif // !THRESHOLD

# ifndef SKIPPED_PIX
#  define SKIPPED_PIX 3
# endif // !SKIPPED_PIX

# ifndef THREAD_NUM
#  define THREAD_NUM 20
# endif // !THREAD_NUM

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1000
# endif // !WIN_WIDTH

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 600
# endif // !WIN_HEIGHT

#define PRINT_VECTOR(v) printf("(%0.3f, %0.3f, %0.3f)\n", v.x, v.y, v.z)
#define PRINT_MAT4X4(v) printf("(%0.3f, %0.3f, %0.3f, %0.3f)\n(%0.3f, %0.3f, %0.3f, %0.3f)\n(%0.3f, %0.3f, %0.3f, %0.3f)\n(%0.3f, %0.3f, %0.3f, %0.3f)\n", v.m[0][0], v.m[0][1], v.m[0][2], v.m[0][3], v.m[1][0], v.m[1][1], v.m[1][2], v.m[1][3], v.m[2][0], v.m[2][1], v.m[2][2], v.m[2][3], v.m[3][0], v.m[3][1], v.m[3][2], v.m[3][3])

#endif // !MACROS_H
