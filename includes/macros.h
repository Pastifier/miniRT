/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:12:40 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 00:46:51 by ebinjama         ###   ########.fr       */
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
#  define WIN_WIDTH 900
# endif // !WIN_WIDTH

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 550
# endif // !WIN_HEIGHT

#endif // !MACROS_H
