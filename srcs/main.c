/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:43:27 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/27 00:55:41 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "rendering.h"
#include "log.h"

int	main(int argc, char *argv[])
{
	static t_program	context;

	init_program(argc, argv, &context);
	render(&context);
	mlx_loop(context.mlx);
	return (0);
}
