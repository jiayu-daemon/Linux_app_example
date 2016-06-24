/* writerec.c */
#include <stdio.h>
#include <stdlib.h>

struct record {
	char name[10];
	int age;
};

int main(void)
{
	struct record array[2] = {{"Ken", 24}, {"Knuth", 28}};
	FILE *fp = fopen("recfile", "w");
	if (fp == NULL) 
	{
		perror("Open file recfile");
		exit(1);
	}
	fwrite(array, sizeof(struct record), 2, fp);
	fclose(fp);
	return 0;
}