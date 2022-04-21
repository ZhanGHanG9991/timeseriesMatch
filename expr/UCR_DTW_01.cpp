#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;
int main(int argc, char *argv[])
{
    // log file pointer
    FILE *lp;
    // data file pointer
    FILE *fp;

    fp = fopen(argv[1], "r");
    lp = fopen(argv[2], "r");

    // 读取的log文件的一个操作
    char op[5];
    // 读取的log文件一个操作后面的data
    char data[100];
    // log文件一个操作后面的起始位置和操作长度
    int st, len;

    // 最终还原出来的修复后的数据
    vector<int> v;
    // 每次读取的一个int数据
    int d;
    // data file的读取第pos个数
    int pos = 0;
    // log文件data的分隔符
    const char *split = ",";
    // log文件data通过split后的每一个char*类型的浮点数
    char *sd;

    while (fscanf(lp, "%s %d %d", op, &st, &len) != EOF)
    {
        while (pos < st)
        {
            fscanf(fp, "%d", &d);
            v.push_back(d);
            pos++;
        }
        if (strcmp(op, "INS") == 0)
        {
            fscanf(lp, "%s", data);
            sd = strtok(data, split);
            while (sd != NULL)
            {
                v.push_back(strtod(sd, NULL));
                sd = strtok(NULL, split);
            }
        }
        else if (strcmp(op, "REP") == 0)
        {
            fscanf(lp, "%s", data);
            sd = strtok(data, split);
            while (sd != NULL)
            {
                v.push_back(strtod(sd, NULL));
                sd = strtok(NULL, split);
            }
            int end = pos + len;
            while (pos < end)
            {
                fscanf(fp, "%d", &d);
                pos++;
            }
        }
        else if (strcmp(op, "DEL") == 0)
        {
            int end = pos + len;
            while (pos < end)
            {
                fscanf(fp, "%d", &d);
                pos++;
            }
        }
    }
    while (fscanf(fp, "%d", &d) != EOF)
    {
        v.push_back(d);
    }
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
    return 0;
}
