#include "tests.h"

static void	draw_square(t_program *context, t_double4 coord, int w, int h)
{
	int	x;
	int	y;
	t_color color;

	cinit(&color, 1, 0, 0);
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_pixel(&context->canvas, coord.x + x, coord.y + y, &color);
			x++;
		}
		y++;
	}
}
void	draw_sphere_using_rt(t_program *context, t_obj *sphere, t_light *plight)
{
	t_double4	ray_origin;
	double		wall_z;
	double		wall_size;
	double		pixel_size;
	double		half;
	double		world_y;
	double		world_x;
	t_double4	pos;
	t_double4	norm;
	t_ray		r;
	t_intersections	xs;
	t_intersection	*hit;

	point(&ray_origin, 0, 0, -5);
	wall_z = 10;
	wall_size = 7;
	pixel_size = wall_size / WIN_WIDTH;
	half = wall_size / 2;
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		world_y = half - pixel_size * y;
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			world_x = -half + pixel_size * x;
			point(&pos, world_x, world_y, wall_z);
			d4sub(&norm, &pos, &ray_origin);
			vnormalize(&norm);
			r = ray(ray_origin, norm);
			ft_bzero(&xs, sizeof(t_intersections));
			intersect_sphere(&r, sphere, &xs);
			hit = get_hit(&xs);
			if (hit)
			{
				hit->p = position(&r, hit->t);
				hit->s_normal = normal_at(hit->obj, &hit->p);
				vector(&hit->eye, -r.direction.x, -r.direction.y, -r.direction.z);
				r.c = lighting(&hit->obj->material, plight, hit, false);
				put_pixel(&context->canvas, x, y, &r.c);
			}
		}
	}
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr,
		0, 0);
}

void	draw_clock(t_program *context)
{
	double radius = (3.0 / 8.0) * WIN_WIDTH;
	double twelfth = M_PI / 6;
	t_double4 twelve = row4(0, radius, 0, 1);
	for (int i = 0; i < 12; i++)
	{
		m4d_rotate_z(&twelve, twelfth * (i + 1));
		m4d_translate(&twelve, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0);
		PRINT_VECTOR(twelve);
		draw_square(context, twelve, 50, 50);
		point(&twelve, 0, radius, 0);
	}
}
void	world_from_chapter_7(void)
{
	t_program context;
	t_world	world;

	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	canvas(&context, WIN_WIDTH, WIN_HEIGHT);

	//t_mat4x4 transformation;
	t_mat4x4 transform_operations;

	point(&world.plight.pos, -10, 10, -10);
	cinit(&world.plight.intensity, 1, 1, 1);

	// Initialize the walls
	t_obj *floor = &world.obj[0];
	//default_plane(floor);
	default_sphere(&world.obj[0]);
	floor->transform = scaling(10, 0.01, 10);
	default_mat(&floor->material);
	cinit(&floor->material.c, 1, 0.9, 0.9);
	floor->material.spec = 0;

	t_obj *left_wall = &world.obj[1];
	default_sphere(&world.obj[1]);
	left_wall->transform = mat4x4_identity();
	transform_operations = translation(0, 0, 5);
	left_wall->transform = mat4x4_cross(&left_wall->transform, &transform_operations);
	transform_operations = rotation_y(-M_PI_4);
	left_wall->transform = mat4x4_cross(&left_wall->transform, &transform_operations);
	transform_operations = rotation_x(M_PI_2);
	left_wall->transform = mat4x4_cross(&left_wall->transform, &transform_operations);
	transform_operations = scaling(10, 0.01, 10);
	left_wall->transform = mat4x4_cross(&left_wall->transform, &transform_operations);
	left_wall->material = floor->material;

	t_obj *right_wall = &world.obj[2];
	default_sphere(&world.obj[2]);
	right_wall->transform = mat4x4_identity();
	transform_operations = translation(0, 0, 5);
	right_wall->transform = mat4x4_cross(&right_wall->transform, &transform_operations);
	transform_operations = rotation_y(M_PI_4);
	right_wall->transform = mat4x4_cross(&right_wall->transform, &transform_operations);
	transform_operations = rotation_x(M_PI_2);
	right_wall->transform = mat4x4_cross(&right_wall->transform, &transform_operations);
	transform_operations = scaling(10, 0.01, 10);
	right_wall->transform = mat4x4_cross(&right_wall->transform, &transform_operations);
	right_wall->material = floor->material;

	t_obj *middle = &world.obj[3];
	default_sphere(&world.obj[3]);
	middle->transform = mat4x4_identity();
	transform_operations = translation(-0.5, 1, 0.5);
	middle->transform = mat4x4_cross(&middle->transform, &transform_operations);
	default_mat(&middle->material);
	cinit(&middle->material.c, 0.1, 1, 0.5);
	middle->material.diff = 0.7;
	middle->material.spec = 0.3;

	t_obj *right = &world.obj[4];
	default_sphere(&world.obj[4]);
	right->transform = mat4x4_identity();
	transform_operations = translation(1.5, 0.5, -0.5);
	right->transform = mat4x4_cross(&right->transform, &transform_operations);
	transform_operations = scaling(0.5, 0.5, 0.5);
	right->transform = mat4x4_cross(&right->transform, &transform_operations);
	default_mat(&right->material);
	cinit(&right->material.c, 0.5, 1, 0.1);
	right->material.diff = 0.7;
	right->material.spec = 0.3;

	t_obj *left = &world.obj[5];
	default_sphere(&world.obj[5]);
	left->transform = mat4x4_identity();
	transform_operations = translation(-1.5, 0.33, -0.75);
	left->transform = mat4x4_cross(&left->transform, &transform_operations);
	transform_operations = scaling(0.33, 0.33, 0.33);
	left->transform = mat4x4_cross(&left->transform, &transform_operations);
	default_mat(&left->material);
	cinit(&left->material.c, 1, 0.8, 0.1);
	left->material.diff = 0.7;
	left->material.spec = 0.3;

	t_double4 camera_origin = row4(0, 0.5, -5, 1); // row4(-2, 1.5, -5, 1);
	t_double4 look_at = row4(0, 1, 0, 1);
	t_double4 up = row4(0, 1, 0, 0);
	t_mat4x4 view = view_transform(&camera_origin, &look_at, &up);

	t_webcam cam = init_camera(WIN_WIDTH, WIN_HEIGHT, M_PI / 3);
	cam.transform = view;

	world.cam = cam;
	t_thread	*threads = init_threads(&context, &world);
	if (!threads)
		return ;

	mlx_loop(context.mlx);
}

void	intersection_test(t_ray *r, t_obj *obj,
bool (*itx_fun)(t_ray *, t_obj *, t_intersections *))
{
	static int	call_count = 1;
	printf("Intersection Test #%d:\n", call_count);

	t_intersections	xs;
	t_intersection	*hit;
	t_ray			ray;


	ft_bzero(&xs, sizeof(t_intersections));

	ray = *r;
	(*itx_fun)(r, obj, &xs);
	PRINT_RAY(ray);
	printf("Generates a hit with obj of type %c at: ", obj->type);
	hit = get_hit(&xs);
	
	int expression = (hit != NULL);
	switch (expression)
	{
	case 1:
		printf("t = %f\n", hit->t);
		printf("With intersection count of: %d\n", xs.count);
		for (int i = 0; i < xs.count; i++)
			printf("xs[%d]: %f\n", i, xs.arr[i].t);
		printf("\n");
		break;
	
	default:
		printf("Nowhere\n\n");
		break;
	}

	call_count++;
}

void	normal_at_test(t_double4 *p, t_obj *obj,
t_double4 (*local_normal_at)(t_obj *, t_double4 *))
{
	static int	call_count = 1;
	printf("Normal at Test #%d:\n", call_count);

	t_double4	norm;
	t_double4	point;

	point = *p;
	norm = (*local_normal_at)(obj, p);

	printf("Normal at for object of type %c at point ", obj->type);
	PRINT_VECTOR_NO_NL(point);
	printf(" is:\n");
	PRINT_VECTOR(norm);
	printf("\n");
	call_count++;
}

void	test_rays_should_miss_cylinder(void)
{
	t_ray	r1, r2, r3;
	t_obj	cy;

	// First ray
	SET_RAY(
		r1,
		1, 0, 0,
		0, 1, 0
	);

	// Second ray
	SET_RAY(
		r2,
		0, 0, 0,
		0, 1, 0
	);

	// Third ray
	SET_RAY(
		r3,
		0, 0, -5,
		1, 1, 1
	);

	// Cylinder
	default_cylinder(&cy);

	// Tests:
	intersection_test(&r1, &cy, intersect_cylinder);
	intersection_test(&r2, &cy, intersect_cylinder);
	intersection_test(&r3, &cy, intersect_cylinder);
}

void	test_rays_should_intersect_cylinder(void)
{
	t_ray	r1, r2, r3;
	t_obj	cy;

	// First ray
	SET_RAY(
		r1,
		1, 0, -5,
		0, 0, 1
	);

	// Second ray
	SET_RAY(
		r2,
		0, 0, -5,
		0, 0, 1
	);

	// Third ray
	SET_RAY(
		r3,
		0.5, 0, -5,
		0.1, 1, 1
	);

	// Cylinder
	default_cylinder(&cy);

	// Tests:
	intersection_test(&r1, &cy, intersect_cylinder);
	intersection_test(&r2, &cy, intersect_cylinder);
	intersection_test(&r3, &cy, intersect_cylinder);
}

void	test_normal_on_cy(void)
{
	t_double4	p1, p2, p3, p4;
	t_obj		cy;

	// Setting up points to test for
	point(&p1, 1, 0, 0);
	point(&p2, 0, 5, -1);
	point(&p3, 0, -2, 1);
	point(&p4, -1, 1, 0);

	default_cylinder(&cy);

	// Tests:
	normal_at_test(&p1, &cy, cy_normal_at);
	normal_at_test(&p2, &cy, cy_normal_at);
	normal_at_test(&p3, &cy, cy_normal_at);
	normal_at_test(&p4, &cy, cy_normal_at);
}

void	test_intersections_on_truncated_cy(void)
{
	t_ray	r[6];
	t_obj	cy;

	SET_RAY(
		r[0],
		0, 1.5, 0,
		0.1, 1, 0
	);
	SET_RAY(
		r[1],
		0, 3, -5,
		0, 0, 1
	);
	SET_RAY(
		r[2],
		0, 0, -5,
		0, 0, 1
	);
	SET_RAY(
		r[3],
		0, 2, -5,
		0, 0, 1
	);
	SET_RAY(
		r[4],
		0, 1, -5,
		0, 0, 1
	);
	SET_RAY(
		r[5],
		0, 1.5, -2,
		0, 0, 1
	);

	// Setting up truncated cylinder
	default_cylinder(&cy);
	cy.cy_min = 1.0;
	cy.cy_max = 2.0;

	for (int i = 0; i < 6; i++)
		intersection_test(&r[i], &cy, intersect_cylinder);
}

void	test_intersections_on_capped_cy(void)
{
	t_ray	r[5];
	t_obj	cy;

	SET_RAY(
		r[0],
		0, 3, 0,
		0, -1, 0
	);
	SET_RAY(
		r[1],
		0, 3, -2,
		0, -1, 2
	);
	SET_RAY(
		r[2],
		0, 4, -2,
		0, -1, 1
	);
	SET_RAY(
		r[3],
		0, 0, -2,
		0, 1, 2
	);
	SET_RAY(
		r[4],
		0, -1, -2,
		0, 1, 1
	);

	// Setting up truncated cylinder
	default_cylinder(&cy);
	cy.cy_min = 1.0;
	cy.cy_max = 2.0;
	cy.cy_closed = true;

	for (int i = 0; i < 5; i++)
		intersection_test(&r[i], &cy, intersect_cylinder);
}


void	test_normal_on_cy_caps(void)
{
	t_double4	p[6];
	t_obj		cy;

	point(&p[0], 0, 1, 0);
	point(&p[1], 0.5, 1, 0);
	point(&p[2], 0, 1, 0.5);
	point(&p[3], 0, 2, 0);
	point(&p[4], 0.5, 2, 0);
	point(&p[5], 0, 2, 0.5);

	// Setting up capped cylinder
	default_cylinder(&cy);
	cy.cy_min = 1.0;
	cy.cy_max = 2.0;
	cy.cy_closed = true;

	for (int i = 0; i < 6; i++)
		normal_at_test(&p[i], &cy, cy_normal_at);
}

void	test_render_simple_cy(void)
{
	t_program	context;
	t_world		world;
	t_obj		cy;

	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	canvas(&context, WIN_WIDTH, WIN_HEIGHT);

	////t_mat4x4 transformation; Leave it for later
	//t_mat4x4 transform_operations;

	point(&world.plight.pos, -10, 10, -10);
	cinit(&world.plight.intensity, 1, 1, 1);

	// Capped Cylinder
	default_cylinder(&cy);
	cy.cy_max = 1.0;
	cy.cy_min = -1.0;
	cy.cy_closed = true;

	t_double4 camera_origin = row4(0, 0, -5, 1); // row4(-2, 1.5, -5, 1);
	t_double4 look_at = row4(0, 0, 0, 1);
	t_double4 up = row4(0, 0, 1, 0);
	t_mat4x4 view = view_transform(&camera_origin, &look_at, &up);

	t_webcam cam = init_camera(WIN_WIDTH, WIN_HEIGHT, M_PI / 3);
	cam.transform = view;

	world.cam = cam;
	t_thread	*threads = init_threads(&context, &world);
	if (!threads)
		return ;

	mlx_loop(context.mlx);
}
