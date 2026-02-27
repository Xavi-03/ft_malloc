CC      := clang
NAME    := ft_malloc
CFLAGS  := -D SHOW_DUMP=1 -D SHOW_MALLOC=1 -D SHOW_MALLOC_INFO=1 -Wall -Werror -Wextra
DEBBUGFLAGS := -D SHOW_DUMP=1 -D SHOW_MALLOC=1 -D SHOW_MALLOC_INFO=1
CALLOCFLAGS := -D CALLOC=1

LIBFT   := ./libft
INCLUDE_DIR := ./include
SRC_DIR := ./src/

LIBFT_LIB := $(LIBFT)
LIBFT_INC := $(LIBFT)/includes

HEADERS := -I $(INCLUDE_DIR) -I $(LIBFT_INC)
LIBS    := -L $(LIBFT_LIB)/ -lft


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

$(OBJ_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): libft $(OBJS) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

debbug: fclean $(NAME)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEBBUGFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
	@$(CC) $(CFLAGS) $(DEBBUGFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

calloc: fclean
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CALLOCFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
	@$(CC) $(CFLAGS) $(CALLOCFLAGS)  $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -s -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libft
