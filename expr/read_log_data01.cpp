#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#define MAX_READ_BUFFER_SIZE 1e5

using namespace std;

// read buffer
double *read_buffer;
int read_buffer_size = 0, read_buffer_pos;
bool has_op;
double per_d;
int data_file_pos = 0, op_st = 0, op_len = 0;
char operation[5], data[50000];
int read_data_pos = 0;
// log文件data的分隔符
const char *split = ",";
// log文件data通过split后的每一个char*类型的浮点数
char *sd;
bool over = false;

int readData(FILE *lp, FILE *fp)
{
    if (read_buffer_size > 0)
    {
        if (read_buffer_pos != read_buffer_size)
        {
            per_d = read_buffer[read_buffer_pos++];
            return 1;
        }
        else
        {
            read_buffer_size = 0;
            read_buffer_pos = 0;
        }
    }
    if (over)
    {
        return 0;
    }
    bool ok = false;
    while (!ok)
    {
        if (has_op == false)
        {
            if (fscanf(lp, "%s %d %d", operation, &op_st, &op_len) != EOF)
            {
                has_op = true;
            }
            else
            {
                while (fscanf(fp, "%lf", &per_d) != EOF)
                {
                    read_buffer[read_buffer_size++] = per_d;
                    if (read_buffer_size == MAX_READ_BUFFER_SIZE)
                    {
                        return readData(lp, fp);
                    }
                }
                over = true;
                return readData(lp, fp);
            }
        }
        while (read_data_pos < op_st && read_buffer_size < MAX_READ_BUFFER_SIZE)
        {
            fscanf(fp, "%lf", &per_d);
            read_buffer[read_buffer_size++] = per_d;
            ok = true;
            read_data_pos++;
        }
        if (read_data_pos < op_st)
        {
            return readData(lp, fp);
        }
        else
        {
            if (strcmp(operation, "INS") == 0)
            {
                fscanf(lp, "%s", data);
                sd = strtok(data, split);
                while (sd != NULL)
                {
                    read_buffer[read_buffer_size++] = strtod(sd, NULL);
                    sd = strtok(NULL, split);
                }
            }
            else if (strcmp(operation, "REP") == 0)
            {
                fscanf(lp, "%s", data);
                sd = strtok(data, split);
                while (sd != NULL)
                {
                    read_buffer[read_buffer_size++] = strtod(sd, NULL);
                    sd = strtok(NULL, split);
                }
                int end = read_data_pos + op_len;
                while (read_data_pos < end)
                {
                    fscanf(fp, "%lf", &per_d);
                    read_data_pos++;
                }
            }
            else if (strcmp(operation, "DEL") == 0)
            {
                int end = read_data_pos + op_len;
                while (read_data_pos < end)
                {
                    fscanf(fp, "%lf", &per_d);
                    read_data_pos++;
                }
            }
            has_op = false;
        }
    }
    return readData(lp, fp);
}

int main(int argc, char *argv[])
{

    // log file pointer
    FILE *lp;
    // data file pointer
    FILE *fp;

    fp = fopen(argv[1], "r");
    lp = fopen(argv[2], "r");

    read_buffer = (double *)malloc(sizeof(double) * (MAX_READ_BUFFER_SIZE + 2000));

    while(readData(lp, fp) == 1) {
        cout << per_d << endl;
    }
    return 0;
}