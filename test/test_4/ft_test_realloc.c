#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *str = "asdsd\n";
	void *ptr = str;
	ptr = realloc(ptr, 100);
}
