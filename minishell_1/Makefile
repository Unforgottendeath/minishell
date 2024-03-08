CC = cc
CFLAGS = -Wall -Wextra -Werror -g -lreadline -fsanitize=address 
SRCS =	utils_1.c \
		utils_2.c \
		redirect_utils.c \
		parsing.c \
		env_utils.c \
		node_utils.c \
		command_utils.c \
		minishell.c \
		split_parsing.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
