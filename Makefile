CC = gcc
NAME = pipex
FLAGS = -Wall -Wextra -Werror
SRC = ft_split.c ft_strjoin.c ft_strlen.c ft_strncmp.c pipex.c 
OBJSRC = $(SRC)

all : $(NAME)

$(NAME): $(OBJSRC)
	$(CC) $(FLAGS) -o $(NAME) $(OBJSRC)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all