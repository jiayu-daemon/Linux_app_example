#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    if((fp =fopen("1.txt","r")) == NULL)
    {
        perror("fopen");
        exit(0);
    }
    perror("fopen");
}
