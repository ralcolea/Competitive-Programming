//============================================================================
// Name        : LightOJ 1205 - Palindromic Numbers
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Counting Range DP
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define N 20

#define ll long long

bool mem[N][N];
ll D[N][N], a, b;
char cad[N], num[N];
int casos, len;
string prefix;

bool isPalin(string c)
{
    if (c.empty())
        return false;

    //cout << "isPalin " << c << "\n";

    int ini = 0;
    int fin = c.length() - 1;
    while (ini <= fin)
    {
        if (c[ini++] != c[fin--])
            return false;
    }
    return true;
}

// function F(k, property)
ll F(int dig, int lastDigit, int current)
{
    if (dig == 0)
    {
        sprintf(num, "%d", current);
        return (ll)(isPalin(prefix + num));
    }

    if (mem[dig][lastDigit])
        return D[dig][lastDigit];

    mem[dig][lastDigit]= 1;
    ll ret = 0LL;
    for (int i = 0; i <= 9; i++)
    {
        ret += F(dig - 1, i, current * 10 + i);
    }

    D[dig][lastDigit] = ret;
    return ret;
}

ll solve(ll x)
{
    ll ret = 0;
    sprintf(cad, "%lld", x);
    len = strlen(cad);
    int remain = len;

    prefix = "";
    for (int i = 0; i < len; i++)
    {
        remain--;
        int d = cad[i] - '0';

        // for all numbers starting with digits less than x[i]
        for (int j = 0; j < d; j++)
        {
            ret += F(remain, j, j);
        }

        // updating property
        prefix = prefix + cad[i];
    }
    return ret;
}

int main()
{
    freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d", &casos);
    for (int i = 1; i <= casos; i++)
    {
        scanf("%lld%lld", &a, &b);
        ll mx = solve(max(a, b) + 1);
        ll mn = solve(min(a, b));
        ll ans = mx - mn;
        printf("Case %d: %lld\n", i, ans);
    }
    return 0;
}
