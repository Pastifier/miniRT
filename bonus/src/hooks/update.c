/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 03:35:28 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/30 11:33:23 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	update(void *context)
{
	// create threads
	// threads will do the rendering
	// join the threads
	if (!pool_init_join(context))
		return (1); // deal with it somehow.
	return (0);
}
