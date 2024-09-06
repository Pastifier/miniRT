/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:54:13 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/06 12:31:38 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTS_H
# define DEFAULTS_H

# include "tests.h"

void	default_world(t_world *world);
void	default_mat(t_mat *mat);
void	default_sphere(t_obj *sphere);
void	default_plane(t_obj *plane);
void	default_cylinder(t_obj *cy);

#endif // !DEFAULTS_H