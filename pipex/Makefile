SRCS    = pipex.c utils.c
OBJS    = ${SRCS:.c=.o}

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

NAME    = pipex

LIBFT_DIR = ./libft
LIBFT_A   = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
