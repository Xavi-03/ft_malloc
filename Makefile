CC      := clang
NAME    := ft_malloc
CFLAGS  := #-g -Wall -Werror -Wextra

LIBFT   := ./libft

INCLUDE_DIR := ./include
SRC_DIR := ./src/

LIBFT_LIB := $(LIBFT)
LIBFT_INC := $(LIBFT)/includes

HEADERS := -I $(INCLUDE_DIR) -I $(LIBFT_INC)
LIBS    := -L $(LIBFT_LIB)


SRCS := src/debbug.c \
		src/galloc.c \
		src/gfree.c \
		src/global_managment.c \
		src/memory_managment.c \
		src/realloc.c \
		src/utils.c \
		src/linked_list/block.c \
		src/linked_list/header.c \
		src/linked_list/linked_list_utils.c \
		src/main.c

OBJ_DIR := obj
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

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
