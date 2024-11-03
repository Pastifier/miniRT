/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:22:17 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/02 19:30:18 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "keys.h"

int	check_state(void *context)
{
	t_program	*state;

	state = (t_program *)context;
	if (state->stop == true)
		destroy_program(context);
	update(context);
	return (0);
}

int	check_keys(int keysym, void *context)
{
	t_program	*state;

	state = (t_program *)context;
	if (keysym == KEY_ESC)
		return (state->stop = true, 0);
	return (0);
}
