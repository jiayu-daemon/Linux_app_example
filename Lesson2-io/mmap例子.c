#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(void)
{
	char *p;
	int fd = open("hello", O_RDWR);
	int i = 0;
	if (fd < 0)
	{
		perror("open hello");
		exit(1);
	}
	
	p = mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) 
	{
		perror("mmap");
		exit(1);
	}
	close(fd);
	
	for(i = 0; i < 6; i++)
	{
	     p[i] = 'a' + i;
	}
	     
	munmap(p, 6);
	return 0;
}