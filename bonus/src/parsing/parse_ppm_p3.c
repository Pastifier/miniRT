/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ppm_p3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:25:25 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/11 20:52:06 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//static bool	_from_p3ppm_to_image(t_p3ppm *image, FILE const *file);

t_p3ppm	*p3ppm_load_from_path(const char *filepath)
{
	t_p3ppm		*image;
	FILE const	*file = fopen(filepath, "r");

	if (!file)
	{
		ft_fprintf(STDERR_FILENO, "FATAL: %s: ", filepath);
		perror("Unable to open file");
		return (NULL);
	}
	image = malloc(sizeof(t_p3ppm));
	if (!image)
	{
		fclose(file);
		return (NULL);
	}
	//if (!_from_p3ppm_to_image(image, file))
	//{
		//free(image);
		//image = NULL;
	//}
	fclose(file);
	return (image);
}
