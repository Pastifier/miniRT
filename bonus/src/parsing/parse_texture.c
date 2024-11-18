/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:39:29 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/16 20:07:46 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "macros.h"

/// @brief Loads a png file onto memory as a `t_canvas`. Ownership of the
/// block thereof is given to the caller.
/// @param filepath the path to the png file to load (No const qualifier
/// to adhere to MiniLibX. The argument however might as well be const).
/// @param context mlx pointer.
/// @return Pointer to the address storing the canvas data.
/// @warning Returns `NULL` on failure or upon not being used in MacOS.
t_canvas	*rt_png_file_to_canvas(char *filepath, void *mlx)
{
	t_canvas	*retval;

	if (!_RT_OS_MACOS_)
		return (NULL);
	retval = malloc(sizeof(t_canvas));
	if (!retval)
		return (NULL);
	retval->ptr = mlx_png_file_to_image(mlx, filepath,
				&retval->tex_width, &retval->tex_height);
	if (!retval->ptr)
	{
		free(retval);
		return (NULL);
	}
	retval->addr = mlx_get_data_addr(retval->ptr, &retval->bpp,
					&retval->line_length, &retval->endian);
	retval->bpp_8 = retval->bpp / 8;
	return (retval);
}

/// @brief Loads a xpm file onto memory as a `t_canvas`. Ownership of the
/// block thereof is given to the caller.
/// @param filepath the path to the xpm file to load (No const qualifier
/// to adhere to MiniLibX. The argument however might as well be const).
/// @param context mlx pointer.
/// @return Pointer to the address storing the canvas data.
/// @warning Returns `NULL` on failure.
t_canvas	*rt_xpm_file_to_canvas(char *filepath, void *mlx)
{
	t_canvas	*retval;

	retval = malloc(sizeof(t_canvas));
	if (!retval)
		return (NULL);
	retval->ptr = mlx_xpm_file_to_image(mlx, filepath,
				&retval->tex_width, &retval->tex_height);
	if (!retval->ptr)
	{
		free(retval);
		return (NULL);
	}
	retval->addr = mlx_get_data_addr(retval->ptr, &retval->bpp,
					&retval->line_length, &retval->endian);
	retval->bpp_8 = retval->bpp / 8;
	return (retval);
}
