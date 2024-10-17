/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:57:40 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 05:44:38 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define _RT_OS_MACOS_ 0
# define _RT_MAX_LIGHTS_ 100
# define _RT_MAX_SHAPES_ 100

# ifdef __MACH__
#  undef _RT_OS_MACOS_
#  define _RT_OS_MACOS_ 1
# endif // !__MACH__

#endif // !MACROS_H