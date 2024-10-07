/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:26:02 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 02:23:51 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"
# include "colors.h"
# include "mlx.h"
# include "macros.h"

bool	create_canvas(t_program *context, int width, int height)
{
	context->canvas.ptr = mlx_new_image(context->mlx, width, height);
	if (!context->canvas.ptr)
		return (false);
	context->canvas.addr = mlx_get_data_addr(\
		context->canvas.ptr, \
		&context->canvas.bpp, \
		&context->canvas.line_length, \
		&context->canvas.endian \
	);
	context->canvas.bpp_8 = context->canvas.bpp / 8;
	return (true);
}

void	put_pixel(t_canvas *canvas, int x, int y, const t_color *color)
{
	char	*dst;

	dst = canvas->addr + (y * canvas->line_length + x * canvas->bpp_8);
	*(uint32_t *)dst = get_color32(color);
}

t_color	fetch_pixel_color(const t_canvas *canvas, int x, int y)
{
	char		*src;
	uint32_t	color_value;
	t_color		ret;

	src = canvas->addr + (y * canvas->line_length + x * canvas->bpp_8);
	color_value = *(uint32_t *)src;
	ret.v.x = (color_value >> 16) & 0xFF;
	ret.v.y = (color_value >> 8) & 0xFF;
	ret.v.z = color_value & 0xFF;
	ret.a = 1;
	if (_RT_OS_MACOS_)
		ret.a = 0;
	ret.r = ret.v.x / 255.999;
	ret.g = ret.v.y / 255.999;
	ret.b = ret.v.z / 255.999;
	return (ret);
}
