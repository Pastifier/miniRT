/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:07 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/04 14:10:55 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "macros.h"
#include "linear_algebra.h"
#include "keys.h"
#include <stdio.h>

void	key_hook(int keycode, t_program *context)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(context->mlx, context->win);
		exit(0);
	}
}