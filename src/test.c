#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* copyfromfile();

int main()
{
   char* mword = copyfromfile(); 
    
    return EXIT_SUCCESS;
}

char* copyfromfile()
{
     FILE* fichier = fopen("src/test.txt", "r");
    if(fichier == NULL) 
    {
        printf("No such file\n");
    }

    char buf[100];
    int i = 0;
    while (fscanf(fichier,"%s", buf) == 1)
    {
        char* word = buf;
        printf("%s\n", word);
        return word;
    }

}
