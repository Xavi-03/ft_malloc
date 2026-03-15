cc test/test_1/ft_full_blocks.c -o test/test_1/ft_full_blocks.out ./libft_malloc_x86_64_Linux.so -Wl,-rpath,.
cc test/test_1/full_blocks.c -o test/test_1/full_blocks.out


cc test/test_2/ft_show_alloc_size.c -o test/test_2/ft_show_alloc_size.out ./libft_malloc_x86_64_Linux.so -Wl,-rpath,.
cc test/test_2/show_alloc_size.c -o test/test_2/show_alloc_size.out


cc test/test_3/ft_test_realloc.c -o test/test_3/ft_test_realloc.out ./libft_malloc_x86_64_Linux.so -Wl,-rpath,.
cc test/test_3/test_realloc.c -o test/test_3/test_realloc.out


cc test/test_4/ft_test_realloc.c -o test/test_4/ft_test_realloc.out ./libft_malloc_x86_64_Linux.so -Wl,-rpath,.
cc test/test_4/test_realloc.c -o test/test_4/test_realloc.out
