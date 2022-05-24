#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void separe(int num);

int main()
{
    separe(52);
    
    return EXIT_SUCCESS;
}

void separe(int num)
{
    while(num != 0)
    {
        int reste = num%10;
        printf("%d ");
        num /= 10; 
    }
}