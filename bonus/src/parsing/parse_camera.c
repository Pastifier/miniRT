/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:11:06 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/16 16:33:24 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

t_mat4s rt_get_cam_inverse(const t_mat4s *view)
{
	t_mat4s ret;

	// Transpose the rotational component (upper-left 3x3 matrix)
	ret.a[0][0] = view->a[0][0];
	ret.a[0][1] = view->a[1][0];
	ret.a[0][2] = view->a[2][0];

	ret.a[1][0] = view->a[0][1];
	ret.a[1][1] = view->a[1][1];
	ret.a[1][2] = view->a[2][1];

	ret.a[2][0] = view->a[0][2];
	ret.a[2][1] = view->a[1][2];
	ret.a[2][2] = view->a[2][2];

	// Compute the new translation components by applying the transposed rotation to the original translation and negating it
	ret.a[0][3] = -(view->a[0][3] * view->a[0][0] + view->a[1][3] * view->a[0][1] + view->a[2][3] * view->a[0][2]);
	ret.a[1][3] = -(view->a[0][3] * view->a[1][0] + view->a[1][3] * view->a[1][1] + view->a[2][3] * view->a[1][2]);
	ret.a[2][3] = -(view->a[0][3] * view->a[2][0] + view->a[1][3] * view->a[2][1] + view->a[2][3] * view->a[2][2]);

	// Set the last row to [0, 0, 0, 1] for homogeneous coordinates
	ret.a[3][0] = 0.0f;
	ret.a[3][1] = 0.0f;
	ret.a[3][2] = 0.0f;
	ret.a[3][3] = 1.0f;

	return ret;
}

bool parse_camera(t_program *context, const t_split *fields, int curr_line)
{
	t_camera *camera;
	char *next;
	float temp;
	t_vec4s forward;
	t_vec4s up;
	t_vec4s left;

	camera = &context->cam;

	if (camera->is_set)
		return (parse_warn_msg(ERR_CAM_DEFINED, curr_line),
			str_arr_destroy(fields->array), false);
	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_CAM_FORMAT, ERR_EXPECT_TYPE_C, curr_line),
			str_arr_destroy(fields->array), false);

	//get position vector
	next = fields->array[1];
	camera->trans.x = ft_atof(next, context);
	next += context->flt_operations + (camera->trans.x <= -0.f);
	camera->trans.y = ft_atof(next, context);
	next += context->flt_operations + (camera->trans.y <= -0.f);
	camera->trans.z = ft_atof(next, context);
	camera->trans.w = 1.0f;


	//Orientation vector here (incomplete)
	/*
		(Normalize everything)
		-Take the vector, cross with J-hat to get left vector
		-Cross with left vector to get true-up vector
		-If the orientation vector is the same as the J-hat or negative J-hat, then the up vector is the same as K-hat
		and the left vector is the same as I-hat.
	*/
	next = fields->array[2];
	forward.x = ft_atof(next, context);
	next += context->flt_operations + (forward.x <= -0.f);
	forward.y = ft_atof(next, context);
	next += context->flt_operations + (forward.y <= -0.f);
	forward.z = ft_atof(next, context);
	forward.w = 0.0f;

	//Normalize the forward vector
	lag_vec4s_normalize(&forward);

	//Get the up vector
	if (forward.x == 0.0f && forward.z == 0.0f)
		up = lag_vec4s_ret(0.0f, 0.0f, 1.0f, 0.0f);
	else
		up = lag_vec4s_cross_ret(forward, lag_vec4s_ret(0.0f, 1.0f, 0.0f, 0.0f));

	//Normalize the up vector
	up = lag_vec4s_normalize_ret(up);

	//Get the left vector
	left = lag_vec4s_cross_ret(up, forward);

	//Normalize the left vector
	left = lag_vec4s_normalize_ret(left);

	//Set the orientation matrix for the cam
	camera->inv_transform = lag_mat4s_rows_ret(
		lag_vec4s_ret(left.x, left.y, left.z, 0.0f),
		lag_vec4s_ret(up.x, up.y, up.z, 0.0f),
		lag_vec4s_ret(-forward.x, -forward.y, -forward.z, 0.0f),
		lag_vec4s_ret(0.0f, 0.0f, 0.0f, 1.0f)
	);
	
	//Set the view matrix
	lag_mat4s_cross_mat4s(camera->inv_transform, lag_mat4s_translation(-camera->trans.x, -camera->trans.y, -camera->trans.z), &camera->inv_transform);
	
	//Set the inverse view matrix
	camera->inv_transform = rt_get_cam_inverse(&camera->inv_transform);

	//get FOV
	temp = ft_atof(fields->array[3], context);
	if (temp < 0.0f || temp > 180.0f)
		return (parse_err_msg(ERR_CAM_FOV, ERR_EXPECT_FOV_RANGE, curr_line),
			str_arr_destroy(fields->array), false);
	camera->fov = temp;

	camera->is_set = true;
	camera->line_set = curr_line;

	camera->scale = lag_vec4sp_ret(1.f, 1.f, 1.f);
	camera->hsize = WIN_WIDTH;
	camera->vsize = WIN_HEIGHT;
	camera->aspect_ratio = (float)camera->hsize / (float)camera->vsize;

	//Calculate the pixel size and half view size
	camera->half_view = tan((camera->fov / 2) * (M_PI / 180.0f));
	if (camera->aspect_ratio >= 1.0f)
	{
		camera->half_width = camera->half_view;
		camera->half_height = camera->half_view / camera->aspect_ratio;
	}
	else
	{
		camera->half_width = camera->half_view * camera->aspect_ratio;
		camera->half_height = camera->half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
	context->cam = *camera;
	return (str_arr_destroy(fields->array), true);
}

