#include "../include/myfilefunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int wordCount(FILE* file, int* lines, int* words, int* chars)
{
    int c;
    int inWord = 0;

    if (file == NULL || lines == NULL || words == NULL || chars == NULL)
    {
        return -1;
    }

    *lines = 0;
    *words = 0;
    *chars = 0;

    while ((c = fgetc(file)) != EOF)
    {
        (*chars)++;

        if (c == '\n')
        {
            (*lines)++;
        }

        if (isspace(c))
        {
            inWord = 0;
        }
        else if (inWord == 0)
        {
            (*words)++;
            inWord = 1;
        }
    }

    return 0;
}


int mygrep(FILE* fp, const char* search_str, char*** matches)
{
    char buffer[1024];
    int count = 0;
    char** temp;

    if (fp == NULL || search_str == NULL || matches == NULL)
    {
        return -1;
    }

    *matches = NULL;

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (strstr(buffer, search_str) != NULL)
        {
            temp = realloc(*matches, (count + 1) * sizeof(char*));

            if (temp == NULL)
            {
                for (int i = 0; i < count; i++)
                {
                    free((*matches)[i]);
                }

                free(*matches);
                *matches = NULL;

                return -1;
            }

            *matches = temp;

            (*matches)[count] = malloc(strlen(buffer) + 1);

            if ((*matches)[count] == NULL)
            {
                for (int i = 0; i < count; i++)
                {
                    free((*matches)[i]);
                }

                free(*matches);
                *matches = NULL;

                return -1;
            }

            strcpy((*matches)[count], buffer);

            count++;
        }
    }

    return count;
}

