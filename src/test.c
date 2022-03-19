#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    char buf[2];
    buf[0] = 'a';
    buf[1] = ' ';

    if(buf[1] == ' ') printf("C le meme\n");
    printf("%d\n", '0');


    return EXIT_SUCCESS;
}