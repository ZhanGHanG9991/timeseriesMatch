#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    FILE *fp; /// data file pointer
    FILE *qp; /// query file pointer

    fp = fopen(argv[1], "r");

    char op[5];
    char data[100];
    int st, len;

    while (fscanf(fp, "%s %d %d", op, &st, &len) != EOF)
    {
        if (strcmp(op, "DEL") == 0)
        {
            printf("%s %d %d\n", op, st, len);
        }
        else
        {
            fscanf(fp, "%s", data);
            printf("%s %d %d %s\n", op, st, len, data);
        }
    }
}
