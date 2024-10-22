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

//---------------------------------//
//----------- ERROR CODES ---------//
//---------------------------------//

# define ERR_AMBIENT_DEFINED "Ambient light already set"
# define ERR_AMBIENT_FORMAT "Invalid format for Ambient Light ratio"
# define ERR_AMBIENT_VALUE "Invalid value for Ambient Light ratio"
# define ERR_AMBIENT_COLOR "Invalid format for Ambient Light color"
# define ERR_AMBIENT_COLOR_VALUE "Invalid value for Ambient Light color"

# define ERR_MAX_LIGHTS "Maximum number of lights reached"
# define ERR_LIGHT_FORMAT "Invalid format for Light Object"
# define ERR_LIGHT_VALUE "Invalid value for Light Object"
# define ERR_LIGHT_COLOR "Invalid format for Light Object color"
# define ERR_LIGHT_COLOR_VALUE "Invalid value for Light Object color"

# define ERR_CAM_DEFINED "Camera is already defined"
# define ERR_CAM_FORMAT "Invalid format for Camera Object"
# define ERR_CAM_FOV "Invalid value for Camera FOV"

# define ERR_MAX_SHAPES "Maximum number of shapes reached"
# define ERR_OBJ_FORMAT "Invalid format for Object"

# define ERR_VEC4_FORMAT "Invalid format for Vector4"

# define ERR_COLOR_FORMAT "Invalid format for Color"
# define ERR_COLOR_VALUE "Invalid value for Color"

# define ERR_EXPECT_FLOAT "Expected: valid floating-point number."
# define ERR_EXPECT_FLOAT_RANGE "Expected: floating-point value in range [0.0, 1.0]"
# define ERR_EXPECT_COLOR_RANGE "Expected: integer value in range [0, 255]"
# define ERR_EXPECT_FOV_RANGE "Expected: floating-point value in range [0.0, 180.0]"
# define ERR_EXPECT_TYPE_A "Expected:\n\tA <ratio> <R>,<G>,<B>"
# define ERR_EXPECT_TYPE_C "Expected:\n\tC <x>,<y>,<z> <ox>,<oy>,<oz> <FOV>"
# define ERR_EXPECT_TYPE_L "Expected:\n\tL <x>,<y>,<z> <ratio> [<R>,<G>,<B>]"
# define ERR_EXPECT_TYPE_SP "Expected:\n\tSP <x>,<y>,<z> <diameter> [<R>,<G>,<B>]"
# define ERR_EXPECT_TYPE_PL "Expected:\n\tPL <x>,<y>,<z> <ox>,<oy>,<oz> [<R>,<G>,<B>]"
# define ERR_EXPECT_TYPE_SQ "Expected:\n\tSQ <x>,<y>,<z> <ox>,<oy>,<oz> <side> [<R>,<G>,<B>]"
# define ERR_EXPECT_TYPE_CY "Expected:\n\tCY <x>,<y>,<z> <ox>,<oy>,<oz> <diameter> <height> [<R>,<G>,<B>]"


#endif // !MACROS_H
