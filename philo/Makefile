NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g 

SRCS = innit.c utils.c out.c philo.c help.c norm.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re