//============================================================================
// Name        : LightOJ 1068: Investigation
// Author      : Rubén Alcolea Núñez
// Copyright   : Your copyright notice
// Description : Dynamic Programming - Digit DP
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define MAXD 15
#define MAXS 105
#define ll long long

int casos;
int k, dp[MAXD][MAXS][MAXS];
ll a, b;
bool mem[MAXD][MAXS][MAXS];

int F(int dig, int sum, int number)
{
    if (dig == 0)
    {
        return (sum % k == 0 && number % k == 0);
    }

    if (mem[dig][sum][number])
        return dp[dig][sum][number];

    mem[dig][sum][number] = true;
    int total = 0;
    for (int i = 0; i <= 9; i++)
        total += F(dig - 1, (sum + i) % k, (number * 10 + i) % k);

    dp[dig][sum][number] = total;
    return total;
}

int solve(ll n)
{
    char x[MAXD];
    sprintf(x, "%lld", n);
    int len = strlen(x);

    int quedan = len;
    int total = 0;

    // both numbers represent the property
    int curr_number = 0;
    int curr_sum = 0;

    for (int i = 0; i < len; i++)
    {
        quedan--;
        int digit = x[i] - '0';
        for (int j = 0; j < digit; j++)
        {
            total += F(quedan, (curr_sum + j) % k, (curr_number * 10 + j) % k);
        }

        curr_sum = (curr_sum + digit) % k;
        curr_number = (curr_number * 10 + digit) % k;
    }
    return total;
}

int main()
{
    //freopen("../build-acm/entrada.txt", "r", stdin);
    scanf("%d", &casos);
    for (int i = 1; i <= casos; i++)
    {
        scanf("%lld%lld%d", &a, &b, &k);
        if (k <= 90)
            printf("Case %d: %d\n", i, solve(b + 1) - solve(a));
        else
            printf("Case %d: 0\n", i);

        memset(dp, 0, sizeof(dp));
        memset(mem, 0, sizeof(mem));
    }
    return 0;
}
