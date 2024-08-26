/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:36:23 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 12:02:39 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

/*--- CONST. DEFINES ---*/

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define DFLT "\x1b[0m"

# ifdef __MACH__
#  define OS_IS_MAC 1
# else
#  define OS_IS_MAC 0
# endif

enum e_exits
{
	EXIT_FATAL = 2
};

void	write_error(const char *msg);

#endif // !LOG_H