#include "../includes/galloc.h"

int main(void) {
	//char *ptr = galloc(1);
	void *ptr1 = galloc(1);
	printf("\n\n\n");
	void *ptr2 = galloc(2);
	printf("\n\n\n");
	void *ptr3 = galloc(3);
	printf("\n\n\n");
	int j = 0;
	while (++j < 120)
		galloc(100);
	galloc(22);
	char *ptr4 = galloc(4);
	printf("\n\n\n");
	char *ptr5 = galloc(200);
	printf("\n\n\n");
	void *ptr6 = galloc(400);
	printf("\n\n\n");
	void *ptr7 = galloc(600);
	printf("\n\n\n");
	void *ptr8 = galloc(50000);
	printf("\n\n\n");
	void *ptr9 = galloc(53244);
	printf("\n\n\n");
	void *ptr10 = galloc(80000);
	printf("\n\n\n");
	t_header *header = get_main_header();
	printf("global %lu\n", header->current_size);
	show_mallocs();

	char *str = "00000000000000000000";
	int i = 0;
	while (str[i])
	{
		ptr5[i] = str[i];
		i++;
	}
	ptr5[i] = '\0';
	char *str1 = "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";
	i = 0;
	while (str1[i])
	{
		ptr4[i] = str1[i];
		i++;
	}
	ptr4[i] = '\0';
	printf("%s\n", str);
	//int i = -1;
	/*while (i < 100000) {
		ptr[++i] = str[0];
		printf("%i\n", i);
	}*/
	//ptr[i] = '\0';
	//printf("%s\n", ptr);
	//printf("%lu\n", sizeof(ptr));
	//printf("%ld\n", sysconf(_SC_PAGESIZE));
	//i = 0;
	/*while (++i < 15000) {
		if (ptr[i] != '\0')
			printf("%c\n", ptr[i]);
			}*/
	//munmap(ptr, 1);
	//printf("%c\n", ptr[2]);
	//printf("%i\n", get_size_header(100));
	//printf("%i\n", get_size_header(500));
	//printf("%i\n", get_size_header(5000));
	return 0;
}
/*struct rlimit rlim;
	getrlimit(RLIMIT_NOFILE, &rlim);
	printf("current %ld\n", rlim.rlim_cur);
	printf("limit %ld\n", rlim.rlim_max);*/
