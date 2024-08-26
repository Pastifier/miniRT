/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:17:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 12:20:30 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "vectors.h"
# include "minirt.h"
# include <stdint.h>

void	pixel_put(t_data *data, t_vector2 point, int color);
uint32_t	assign_color(uint8_t r,uint8_t g, uint8_t b);

#endif // !RENDERING_H