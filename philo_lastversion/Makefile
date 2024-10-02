NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread -g 

SRCS = innit.c utils.c out.c philo.c help.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re