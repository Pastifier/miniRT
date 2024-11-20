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

# define WIN_WIDTH 1600
# define WIN_HEIGHT  900

# define _RT_OS_MACOS_ 0
# define _RT_MAX_LIGHTS_ 100
# define _RT_MAX_SHAPES_ 100

# define _RT_SKIP_STEP 3
# define _RT_LERP_THRESH 20

# ifndef _RT_REFLECTION_DEPTH
#  define _RT_REFLECTION_DEPTH 4
# endif // !_RT_REFLECTION_DEPTH

# ifndef SPOTLIGHT_FALLOFF
#  define SPOTLIGHT_FALLOFF 2.0f
# endif // !SPOTLIGHT_FALLOFF

# define _RT_NUM_THREADS 10

# define _RT_MAX_ITX 200
# define _RT_MIN_INTENSITY 0.05f

# define MOVE_SPEED 5.f
# define PITCH_SPEED 0.3f
# define YAW_SPEED 0.3f

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
# define ERR_OBJ_VALUE "Invalid value for Object Attribute"

# define ERR_VEC4_FORMAT "Invalid format for Vector4"

# define ERR_COLOR_FORMAT "Invalid format for Color"
# define ERR_COLOR_VALUE "Invalid value for Color"

# define ERR_FLOAT_VALUE "Invalid value for floating-point number"

# define ERR_M_FORMAT "Invalid format for Material"
# define ERR_M_VALUE "Invalid value for Material Attribute"

# define ERR_M_BUMP_FORMAT "Invalid format for Bump Map"
# define ERR_M_CHECKER "Invalid format for Checker Map"

# define ERR_EXPECT_CHECKER "Expected: checker=<yes/no>"
# define ERR_EXPECT_XPM "Expected: XPM file"
# define ERR_EXPECT_M "Expected: M <material.trait>=<float>,<material.trait>"
# define ERR_EM2 "=<float>,<etc>\n\tUsing default values...\n"
# define ERR_EXPECT_M_TRAIT "Expected: Valid Material Trait: [ambient, "
# define ERR_EMT2 "diffuse, specular, sheen]\n\tUsing default values...\n"
# define ERR_EXPECT_FLOAT "Expected: valid floating-point number."
# define ERR_EXPECT_INT "Expected: valid integer number."
# define ERR_EXPECT_TUPLE "Expected: Tuple in the format <x>,<y>,<z>"
# define ERR_EXPECT_F_RANGE "Expected: floating-point value in range [0.0, 1.0]"
# define ERR_EXPECT_COLOR_RANGE "Expected: integer value in range [0, 255]"
# define ERR_EXPECT_COLOR_FORMAT "Expected: Color in the format <R>,<G>,<B>"
# define ERR_E_FOV_RANGE "Expected: floating-point value in range [0.0, 180.0]"
# define ERR_EXPECT_TYPE_A "Expected:\n\tA <ratio> <R>,<G>,<B>"
# define ERR_EXPECT_TYPE_C "Expected:\n\tC <x>,<y>,<z> <ox>,<oy>,<oz> <FOV>"
# define ERR_EXPECT_TYPE_L "Expected:\n\tL <x>,<y>,<z> <ratio> [<R>,<G>,<B>]"
# define ERR_EXPECT_TYPE_SL "Expected:\n\tSL <x>,<y>,<z> <ox>,<oy>,<oz> "
# define ERR_ESL "<ratio> <spot_angle> [<R>,<G>,<B>]"
# define ERR_E_TYPE_SP "Expected:\n\tsp <x>,<y>,<z> <diameter> [<R>,<G>,<B>]"
# define ERR_E_T_PL "Expected:\n\tpl <x>,<y>,<z> <ox>,<oy>,<oz> [<R>,<G>,<B>]"
# define ERR_EXPECT_TYPE_CY "Expected:\n\tcy <x>,<y>,<z> <ox>,<oy>,<oz> "
# define ERR_ECY "<diameter> <height> [<R>,<G>,<B>]"
# define ERR_EXPECT_TYPE_CU "Expected:\n\tcu <x>,<y>,<z> <ox>,<oy>,<oz> "
# define ERR_ECU "<side> [<R>,<G>,<B>]"
# define ERR_EXPECT_TYPE_CO "Expected:\n\tco <x>,<y>,<z> <ox>,<oy>,<oz> "
# define ERR_ECO "<diameter> <height> [<R>,<G>,<B>]"

#endif // !MACROS_H
