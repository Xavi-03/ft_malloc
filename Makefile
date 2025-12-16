CC      := clang
NAME    := ft_malloc
CFLAGS  := -g -Wall -Werror -Wextra

LIBFT   := ./libs/libft

INCLUDE_DIR := ./include
SRC_DIR := ./src/

LIBFT_LIB := $(LIBFT)
LIBFT_INC := $(LIBFT)/includes

HEADERS := -I $(INCLUDE_DIR) -I $(LIBFT_INC)
LIBS    := -L $(LIBFT_LIB)

SRCS := *.c */*.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)


libft: Makefile
	@make -s -C $(LIBFT)

%.o: %.c $(HEADERS) Makefile
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): libft $(OBJS) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make -s -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -s -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libft
