/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:17:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 14:58:30 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "minirt.h"
# include "vectors.h"
# include "ray.h"
# include <stdint.h>

void		pixel_put(t_data *data, t_vector2 point, int color);
uint32_t	assign_color(uint8_t r,uint8_t g, uint8_t b);
uint32_t	ray_color(t_ray *ray);

#endif // !RENDERING_H
