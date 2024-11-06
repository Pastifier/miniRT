/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 03:35:28 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/06 17:12:51y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <time.h>

static inline float get_delta_time(struct timespec* prev,
						struct timespec* curr)
{
	return ((curr->tv_sec - prev->tv_sec) + \
		(curr->tv_nsec - prev->tv_nsec) / 1e9f);
}

int	update(void *context)
{
	static struct timespec	last_time;
	struct timespec			curr_time;

	clock_gettime(CLOCK_MONOTONIC, &curr_time);
	if (last_time.tv_sec != 0 || last_time.tv_nsec != 0)
	{
		((t_program*)context)->delta_time = \
			get_delta_time(&last_time, &curr_time);
	}
	last_time = curr_time;
	if (!pool_init_join(context))
		return (1);
	return (0);
}
