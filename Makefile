NAME	:= philo
CC		:= gcc
CCFLAGS :=  -pthread #-Wall -Werror -Wextra -g -fsanitize=thread
RM		:= rm -rf

SRC_DIR	:= src
SRCS =	$(SRC_DIR)/philo.c \
		$(SRC_DIR)/check_args.c \
		$(SRC_DIR)/libft.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/philo_life.c

OBJ_DIR := obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY : all fclean clean re
