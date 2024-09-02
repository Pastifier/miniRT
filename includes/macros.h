/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:12:40 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/02 15:39:50 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# ifdef __MACH__
#  define OS_MACOS 1
# else
#  define OS_MACOS 0
# endif // !__MACH__

# ifndef WIN_WIDTH
#  define WIN_WIDTH 800
# endif // !WIN_WIDTH

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 800
# endif // !WIN_HEIGHT

#endif // !MACROS_H
