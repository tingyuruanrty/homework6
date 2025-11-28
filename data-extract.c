#include <stdlib.h>
#include <stdio.h>

/* This function copies integers from file infp to file outfp. */
int copy_integers(FILE *outfp, FILE *infp, int start, int end)
{
    /* TODO: Copy integers from start to end.
         You may like to use the functions fseek(), fread() and fwrite() to accomplish this task. Check man pages for details.
         Return 0 upon successful completion. Otherwise, return -1. */

    int buffer;

    if (fseek(infp, 4 * start, SEEK_SET) != 0)
    {
        return -1;
    }
    if (fseek(outfp, 4 * start, SEEK_SET) != 0)
    {
        return -1;
    }

    for (int i = start; i < end + 1; ++i)
    {
        if (fread(&buffer, 4, 1, infp) != 4)
        {
            return -1;
        }
        if (fwrite(buffer, 4, 1, outfp) != 4)
        {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Usage: %s <input-filename> <output-filename> range [range ..]\n", argv[0]);
        return -1;
    }

    FILE *infp, *outfp;

    /* TODO: Open the input and output files for read and write operations respectively. If the operations fail, return -1. */
    infp = fopen(argv[1], "r+");
    if (infp == NULL)
    {
        printf("open inputfile failed\n");
        return -1;
    }

    outfp = fopen(argv[2], "w+");
    if (outfp == NULL)
    {
        printf("open outputfile failed\n");
        return -1;
    }

    for (int i = 3; i < argc; i++)
    {
        int start, end;
        if (sscanf(argv[i], "%d-%d", &start, &end) != 2)
        {
            if (sscanf(argv[i], "%d", &start) != 1)
            {
                printf("Invalid range!\n");
                return -1;
            }
            end = start;
        }

        if (start < 0 || end < 0 || end < start)
        {
            printf("Start and end must be >= 0 and start must be <= end\n");
            return -1;
        }
        if (copy_integers(outfp, infp, start, end))
        {
            printf("copy_integers() returned an error.\n");
            return -1;
        }
    }

    /* TODO: Close the files. If the operations fail, return -1. */
    if (fclose(infp) == EOF)
    {
        printf("close inputfile failed\n");
        return -1;
    }
    if (fclose(outfp) == EOF)
    {
        printf("open outputfile failed\n");
        return -1;
    }
    return 0;
}
