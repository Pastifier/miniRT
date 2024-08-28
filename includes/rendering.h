/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:17:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 13:51:27 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "vectors.h"
# include "minirt.h"
# include <stdint.h>

void		pixel_put(t_data *data, t_vector2 point, int color);
uint32_t	assign_color(uint8_t r,uint8_t g, uint8_t b);
uint32_t	convert_to_color(float r, float g, float b);
void		render(t_program *context);
void		update_camera(t_camera *camera);

#endif // !RENDERING_H
