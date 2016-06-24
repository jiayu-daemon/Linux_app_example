#include <stdio.h>

int main()
{
    int i = 0;
    int total = 0;

    for(i=1; i<101; i++)
        total = total +i;

    printf("The result is %d\n",total);

    return 0;
}
