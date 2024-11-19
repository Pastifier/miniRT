# Necessities
CC := cc
CFLAGS = -Wextra -Wall -Werror -lz -Wno-unused-result -mavx -mavx2 -O3 -flto -funroll-loops -fno-signed-zeros#-g -fsanitize=address,undefined

# OS-specification
OS := $(shell uname)

Dar = Darwin

Lin = Linux

ifeq (${OS}, ${Dar})
	BUILD_DIR := minilibx_macos
	MLX := mlx
	CFLAGS += -L$(BUILD_DIR) -I$(BUILD_DIR) -l$(MLX) -framework OpenGL -framework Appkit -Llibft -Ilibft/includes -lft -L/usr/lib -lm
else ifeq (${OS}, ${Lin})
	BUILD_DIR := minilibx_linux
	MLX := mlx_Linux
	CFLAGS += -L$(BUILD_DIR) -I$(BUILD_DIR) -l$(MLX) -L/usr/lib -lXext -lX11 -lm -lz -Llibft -Ilibft/includes -lft
else
	$(error Idk, man. Doesn't look like something I was BUILT to deal with ;3)
endif

# PROJECT
NAME := miniRT

SRC := main.c ft_atof.c rays.c fragment.c sort.c lighting.c refractions.c reflections.c lerp.c lighting_utils.c\
			$(addprefix colors/, canvas.c paint.c color_op.c) \
			$(addprefix parsing/, parse.c parse_ambient.c parse_light.c \
				parse_camera.c parse_sphere.c parse_utils.c parse_errors.c \
				parse_plane.c parse_cylinder.c parse_cube.c parse_cone.c \
				parse_extras.c parse_material.c parse_texture.c parse_xpm.c) \
			$(addprefix destroy/, destroy.c) \
			$(addprefix threads/, init_join.c routines.c) \
			$(addprefix world/, itx_test_world.c) \
			$(addprefix hooks/, update.c keys.c mouse.c) \
			$(addprefix intersections/, sphere_test.c plane.c shape_utils.c cylinder.c cube.c cone.c) \
			$(addprefix textures/, textures.c parametrizations.c tangents.c)
SRC_DIR :=	src
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

LAG_SRC := $(addprefix vec4_la_ps/, init_ps.c ps_extra.c simple_operations_1_ps.c simple_operations_2_ps.c simple_operations_3_ps.c \
									linear_algebra_1_ps.c linear_algebra_2_ps.c) \
			$(addprefix mat4_la_ps/, mat4s_init.c mat4s_init_rot.c \
									mat4s_cross.c mat4s_transform_inverse.c)
LAG_DIR := $(SRC_DIR)/LagAMat
LAG_SRCS := $(addprefix $(LAG_DIR)/, $(LAG_SRC))

INC := miniRT.h common.h colors.h canvas.h macros.h keys.h ltypes.h lag.h
INC_DIR := include
INCLUDE := $(addprefix $(INC_DIR)/, $(INC))
all: $(NAME)

$(NAME): $(SRCS) $(LAG_SRCS) $(INCLUDE)
	@make -C $(BUILD_DIR)
	make -C libft
	$(CC) -o $(NAME) -I$(INC_DIR) $(SRCS) $(LAG_SRCS) $(CFLAGS)

clean:
	@make -C $(BUILD_DIR) clean
	make -C libft clean

fclean:
	@make -C $(BUILD_DIR) clean
	rm -rf $(BUILD_DIR)/lib$(MLX).a
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
