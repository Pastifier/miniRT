# Necessities
CC := cc
CFLAGS = -Wextra -Werror -Wall -mavx -mavx2 -O3 -march=native -funroll-loops -fno-signed-zeros

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

SRC := main.c ft_atof.c rays.c fragment.c sort.c lighting.c refractions.c \
			$(addprefix colors/, canvas.c paint.c color_op.c) \
			$(addprefix parsing/, parse.c parse_ambient.c parse_light.c \
				parse_camera.c parse_sphere.c parse_utils.c parse_errors.c \
				parse_plane.c parse_cylinder.c parse_cube.c) \
			$(addprefix destroy/, destroy.c) \
			$(addprefix threads/, init_join.c routines.c) \
			$(addprefix world/, itx_test_world.c) \
			$(addprefix hooks/, update.c) \
			$(addprefix intersections/, sphere_test.c)
SRC_DIR :=	src
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

INC := miniRT.h common.h colors.h canvas.h macros.h keys.h
INC_DIR := include
INCLUDE := $(addprefix $(INC_DIR)/, $(INC))
all: $(NAME)

$(NAME): $(SRCS) $(INCLUDE)
	@make -C $(BUILD_DIR)
	make -C libft
	$(CC) -o $(NAME) -I$(INC_DIR) -ILagAMat/include $(SRCS) $(CFLAGS)

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
