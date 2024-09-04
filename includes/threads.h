/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:02:47 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/04 13:56:50 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# ifndef THREAD_NUM
#  define THREAD_NUM 16
# endif // !THREAD_NUM

# include "miniRT.h"
# include "pthread.h"
# include "render.h"

typedef struct s_thread
{
	// its id;
	int	id;
	// a pointer to context;
	t_program	*context;
	// possibly too, if not stored within context, a pointer to the world;
	t_world		*world;
	// obviously, a pthread_t as well
	pthread_t	thread;
	// and
}	t_thread;

t_thread	*init_threads(t_program *context, t_world *world);

#endif // !THREADS_H