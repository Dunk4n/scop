# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 16:00:17 by niduches          #+#    #+#              #
#    Updated: 2020/06/17 01:35:34 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

D_SRC		=	./src/
D_INC		=	./include/

BUILD_DIR	=	build

SRC_PATH	=	main.c				\
				init.c				\
				shader.c			\
				math.c				\
				math_vector.c		\
				mesh.c				\
				camera.c			\
				load_obj.c			\
				obj.c				\
				parse_utils.c		\
				parse_vertex.c		\
				parse_face.c		\
				parse_group.c		\
				parse_obj.c			\
				parse_s.c			\
				parse_mtl.c			\
				format_obj.c		\
				delete.c			\
				load_gl.c			\
				draw.c				\
				update.c			\
				get_bmp.c			\
				preprocess.c		\
				update_matrix.c		\
				load_mtl.c			\
				parse_mtl_one_arg.c	\
				parse_mtl_args.c	\

SRC			=	$(addprefix $(D_SRC),$(SRC_PATH))

NAME		=	scop

OBJ			=	$(SRC:%.c=$(BUILD_DIR)/%.o)

CFLAGS		=	-I$(D_INC) -Wall -Wextra #-Werror

LDFLAGS		=	-L./libft/ -lft -lm -lGL -lX11 -lSDL2 -lGLEW

all:	$(NAME)

options:
	@echo "  CC       $(CC)"
	@echo "  CFLAGS   $(CFLAGS)"
	@echo "  LDFLAGS  $(LDFLAGS)"

$(BUILD_DIR)/%.o: %.c $(INC)
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	@echo "  RM       $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@make -C libft/ fclean
	@echo "  RM       $(NAME)"
	@rm -f $(NAME) *~

$(NAME): options $(OBJ)
	@make -C libft/
	@echo "  BUILD    $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS) ./libft/libft.a

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all options clean fclean re
