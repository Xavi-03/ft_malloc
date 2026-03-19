ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC      := clang
NAME    := libft_malloc_$(HOSTTYPE).so
LINK    := libft_malloc.so
CFLAGS  := -g -Wall -Werror -Wextra -fPIC
DUMPFLAG	:= -D SHOW_DUMP=1
ALLOCFLAG	:= -D SHOW_MALLOC=1
ALLOCINFOFLAS	:= -D SHOW_MALLOC_INFO=1
DEBBUGFLAGS := $(DUMPFLAG) $(ALLOCFLAG) $(ALLOCINFOFLAS)
CALLOCFLAGS := -D CALLOC=1

LIBFT   := ./libft
INCLUDE_DIR := ./include
SRC_DIR := ./src/

LIBFT_LIB := $(LIBFT)
LIBFT_INC := $(LIBFT)/includes

HEADERS := -I $(INCLUDE_DIR) -I $(LIBFT_INC)
LIBS    := -L $(LIBFT_LIB)/ -lft


SRCS := src/malloc.c \
		src/realloc.c \
		src/free.c \
		src/linked_list/block.c \
		src/linked_list/header.c \
		src/managment/global_managment.c \
		src/managment/memory_managment.c \
		src/utils/linked_list_utils.c \
		src/utils/debbug.c \
		src/utils/utils.c


OBJ_DIR := obj
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)


libft: Makefile
	@make -s -C $(LIBFT)

$(OBJ_DIR)/%.o: %.c ./libft/libft.a $(SRCS) Makefile ./includes/galloc.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): libft $(OBJS) Makefile ./includes/galloc.h
	@$(CC) -shared $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@ln -sf $(NAME) $(LINK)


clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LINK)
	@make -s -C $(LIBFT) fclean

re: fclean all

debbug: CFLAGS += $(DEBBUGFLAGS)
debbug: re

calloc: CFLAGS += $(CALLOCFLAGS)
calloc: re

dump: CFLAGS += $(DUMPFLAG)
dump: re

alloc: CFLAGS += $(ALLOCFLAG)
alloc: re

alloc_info: CFLAGS += $(ALLOCINFOFLAS)
alloc_info: re

.PHONY: all clean fclean re libft debbug calloc dump alloc alloc_info
