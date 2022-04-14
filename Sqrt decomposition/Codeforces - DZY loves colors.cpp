//============================================================================
// Name        : Codeforces 254 Div 1 Problem C: DZY Loves Colors
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Sqrt Decomposition
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAXN 100005
#define MAXSQR 330

#define ll long long

int N, K, a, b, curr;
int SQRSize, type;
ll upd_numbers[MAXSQR], sum_colors[MAXSQR], upd_colors[MAXSQR];
ll numbers[MAXN], colors[MAXN], value;

void update(int a, int b, ll value)
{
    int x = a / SQRSize;
    int y = b / SQRSize;

    if (x == y)
    {   // same block
        for (int val = a; val <= b; val++)
        {
            ll deltha = upd_numbers[x] ? abs(value - upd_numbers[x]) :
                                         abs(value - numbers[val]);

            // updating colorfulness
            colors[val] += deltha;

            // updating sum of colors
            sum_colors[x] += deltha;

            // updating current color
            numbers[val] = value;
        }
        // updating state of first group: partial or complete
        if (b - a + 1 == SQRSize)
            upd_numbers[x] = value; // complete
        else
        {
            // updating previous values
            if (upd_numbers[x])
            {
                for (int val = x * SQRSize; val < a; val++)
                    numbers[val] = upd_numbers[x];

                for (int val = b + 1; val < (x+1)*SQRSize; val++)
                    numbers[val] = upd_numbers[x];
            }
            upd_numbers[x] = 0;     // partial
        }
    }
    else
    {
        // processing first block
        curr = 0;
        for (int val = a; val < (x + 1) * SQRSize; val++)
        {
            ll deltha = upd_numbers[x] ? abs(value - upd_numbers[x]) :
                                         abs(value - numbers[val]);

            // updating colorfulness
            colors[val] += deltha;

            // updating sum of colors
            sum_colors[x] += deltha;

            // updating current color
            numbers[val] = value;

            curr++;
        }

        // updating state of first group: partial or complete
        if (curr == SQRSize)
            upd_numbers[x] = value; // complete
        else
        {
            // updating previous values
            if (upd_numbers[x])
            {
                for (int val = x * SQRSize; val < a; val++)
                    numbers[val] = upd_numbers[x];
            }
            upd_numbers[x] = 0;     // partial
        }

        // processing middle blocks
        for (int val = x + 1; val < y; val++)
        {
            if (upd_numbers[val])
            {
                sum_colors[val] += abs(value - upd_numbers[val]) * SQRSize;

                upd_colors[val] += abs(value - upd_numbers[val]);
            }
            else
            {
                int ini = val * SQRSize;
                int fin = (val + 1) * SQRSize;
                for (int curr = ini; curr < fin; curr++)
                {
                    colors[curr] += abs(value - numbers[curr]);

                    sum_colors[val] += abs(value - numbers[curr]);

                    numbers[curr] = value;
                }
            }

            upd_numbers[val] = value;
        }

        // processing last block
        curr = 0;
        for (int val = y * SQRSize; val <= b; val++)
        {
            ll deltha = upd_numbers[y] ? abs(value - upd_numbers[y]) :
                                         abs(value - numbers[val]);

            // updating colorfulness
            colors[val] += deltha;

            // updating sum of colors
            sum_colors[y] += deltha;

            // updating current color
            numbers[val] = value;

            curr++;
        }

        // updating state of last block: partial or complete
        if (curr == SQRSize)
            upd_numbers[y] = value; // complete
        else
        {
            // updating previous values
            if (upd_numbers[y])
            {
                for (int val = b + 1; val < (y + 1) * SQRSize; val++)
                    numbers[val] = upd_numbers[y];
            }
            upd_numbers[y] = 0;     // partial
        }
    }
}

ll query(int a, int b)
{
    ll total = 0;

    int x = a / SQRSize;
    int y = b / SQRSize;

    if (x == y)
    {
        for (int val = a; val <= b; val++)
        {
            total += colors[val] + upd_colors[x];
        }
    }
    else
    {
        // processing first block
        for (int val = a; val < (x + 1) * SQRSize; val++)
            total += colors[val] + upd_colors[x];

        // processing middle blocks
        for (int val = x + 1; val < y; val++)
            total += sum_colors[val];

        // processing last block
        for (int val = y * SQRSize; val <= b; val++)
            total += colors[val] + upd_colors[y];
    }

    return total;
}

void solve()
{
    // processing queries
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &type);
        if (type == 1)
        {
            scanf("%d %d %I64d", &a, &b, &value);
            update(a - 1, b - 1, value);
        }
        else if (type == 2)
        {
            scanf("%d%d", &a, &b);
            printf("%I64d\n", query(a - 1, b - 1));
        }
    }
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d%d", &N, &K);
    SQRSize = sqrt(N) + 1;

    for (int i = 0; i <= SQRSize; i++)
        sum_colors[i] = upd_numbers[i] = upd_colors[i] = 0;

    for (int i = 0; i < N; i++)
    {
        numbers[i] = i + 1;
        colors[i] = 0;
    }

    solve();
    return 0;
}
