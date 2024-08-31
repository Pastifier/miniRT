#include "render.h"
#include "rtmath.h"
#include "objects.h"
#include "linear_algebra.h"
#include <stdio.h>
#include "matrix.h"
#include "mlx.h"
#include "macros.h"

void render_clock(t_program *context)
{
	int center_x = WIN_WIDTH / 2;
	int center_y = WIN_HEIGHT / 2;

	int num_hours = 12;
	double angle_increment = 2 * M_PI / num_hours;
	double initial_radius = (center_y / 2.0);
	t_double4 p;
	point(&p, initial_radius, 0.0, 0.0);
	t_mat4x4 scale_matrix = scaling(0.5, 0.5, 0.5);
	p = mat4x4_cross_vec(&scale_matrix, &p);
	for (int i = 0; i < num_hours; i++)
	{
		t_mat4x4 rotation_matrix = rotation_z(i * angle_increment);
		t_double4 rotated_p = mat4x4_cross_vec(&(rotation_matrix), &p);

		rotated_p.x += center_x;
		rotated_p.y += center_y;

		if ((int)rotated_p.x >= 0 && (int)rotated_p.x < WIN_WIDTH && (int)rotated_p.y >= 0 && (int)rotated_p.y < WIN_HEIGHT)
		{
			t_color c;
			color(&c, 1.0, 1.0, 1.0);
			put_pixel(&context->canvas, (int)rotated_p.x, (int)rotated_p.y, &c);
		}
	}
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
}