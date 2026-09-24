#include <stdio.h>
#include <stdlib.h>

#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main()
{
    printf("--- Testing String Functions ---\n");

    /* Testing mystrlen */
    const char *text = "Hello World";
    int length = mystrlen(text);

    printf("mystrlen(\"%s\") = %d\n", text, length);


    /* Testing mystrcpy */
    char dest1[50];

    int copied = mystrcpy(dest1, "Hello C");

    printf("mystrcpy() = \"%s\"\n", dest1);
    printf("Characters copied = %d\n", copied);


    /* Testing mystrncpy */
    char dest2[50];

    int copied_n = mystrncpy(dest2, "Operating Systems", 10);

    printf("mystrncpy() = \"%s\"\n", dest2);
    printf("Characters processed = %d\n", copied_n);


    /* Testing mystrcat */
    char dest3[100] = "Hello ";

    int total = mystrcat(dest3, "World");

    printf("mystrcat() = \"%s\"\n", dest3);
    printf("Total characters = %d\n", total);


    printf("\n--- Testing File Functions ---\n");

    /* Create a test file */
    FILE *file = fopen("test.txt", "w");

    if (file == NULL)
    {
        printf("Error: Could not create test.txt\n");
        return 1;
    }

    fprintf(file, "Hello world\n");
    fprintf(file, "This is C programming\n");
    fprintf(file, "Operating Systems\n");
    fprintf(file, "Hello again\n");

    fclose(file);


    /* Test wordCount */
    file = fopen("test.txt", "r");

    if (file == NULL)
    {
        printf("Error: Could not open test.txt\n");
        return 1;
    }

    int lines = 0;
    int words = 0;
    int chars = 0;

    int result = wordCount(file, &lines, &words, &chars);

    fclose(file);

    if (result == 0)
    {
        printf("wordCount():\n");
        printf("Lines      = %d\n", lines);
        printf("Words      = %d\n", words);
        printf("Characters = %d\n", chars);
    }
    else
    {
        printf("wordCount() failed\n");
    }


    /* Test mygrep */
    file = fopen("test.txt", "r");

    if (file == NULL)
    {
        printf("Error: Could not open test.txt\n");
        return 1;
    }

    char **matches = NULL;

    int match_count = mygrep(file, "Hello", &matches);

    fclose(file);

    if (match_count == -1)
    {
        printf("mygrep() failed\n");
    }
    else
    {
        printf("\nmygrep(\"Hello\") found %d matches:\n", match_count);

        for (int i = 0; i < match_count; i++)
        {
            printf("%s", matches[i]);
            free(matches[i]);
        }

        free(matches);
    }


    return 0;
}
