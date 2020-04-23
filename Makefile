# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 16:00:17 by niduches          #+#    #+#              #
#    Updated: 2020/04/22 15:21:37 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

D_SRC		=	./src/
D_INC		=	./include/

BUILD_DIR	=	build

SRC_PATH	=	main.c			\
				init.c			\
				shader.c		\
				math.c			\
				math_vector.c	\
				mesh.c			\
				camera.c		\

SRC			=	$(addprefix $(D_SRC),$(SRC_PATH))

NAME		=	a.out

OBJ			=	$(SRC:%.c=$(BUILD_DIR)/%.o)

CFLAGS		=	-I$(D_INC) -Wall -Wextra #-Werror

LDFLAGS		=	-lm -lGL -lX11 -lSDL2 -lGLEW

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
	@echo "  RM       $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo "  RM       $(NAME)"
	@rm -f $(NAME) *~

$(NAME): options $(OBJ)
	@echo "  BUILD    $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all options clean fclean re
