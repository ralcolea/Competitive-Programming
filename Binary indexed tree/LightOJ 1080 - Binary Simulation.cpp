//============================================================================
// Name        : 1080 - Binary Simulation
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <bits/stdc++.h>
 
using namespace std;
#define MAX 100005
 
int Q, casos, a, b;
int N, fenwick[MAX], number = 1;
char s[MAX], c;
 
void update(int index, int value)
{
    while (index <= N)
    {
        fenwick[index] += value;
        index += (index & -index);
    }
}
 
int read(int index)
{
    int sum = 0;
    while (index > 0)
    {
        sum += fenwick[index];
        index -= (index & -index);
    }
    return sum;
}
 
int main()
{
    scanf("%d", &casos);
    while (casos--)
    {
        scanf("%s", s + 1);
        N = strlen(s + 1);
 
        scanf("%d\n", &Q);
        memset(fenwick, 0, sizeof(fenwick));
 
        printf("Case %d:\n", number++);
        for (int i = 0; i < Q; i++)
        {
            scanf("%c", &c);
            if (c == 'I')
            {
                scanf("%d%d\n", &a, &b);
                update(a, +1);
                update(b + 1, -1);
            }
            else if (c == 'Q')
            {
                scanf("%d\n", &a);
                printf("%d\n", (s[a] - '0' + read(a)) % 2);
            }
        }
    }
 
    return 0;
}