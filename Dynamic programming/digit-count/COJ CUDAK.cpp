//============================================================================
// Name        : COJ 2481 - CUDAK
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : DP Digit
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAXN 20
#define MAXSUM 140
#define ll long long

bool mem[MAXN][MAXSUM];
ll D[MAXN][MAXSUM], a, b, curr_solution;
int s;
char cad[MAXN];

ll F(int dig, int sum)
{
    if (dig == 0)
    {
        return (ll)(sum == 0);
    }

    if (mem[dig][sum])
        return D[dig][sum];

    mem[dig][sum] = 1;
    ll total = 0LL;
    for (int i = 0; i <= 9; i++)
        total += F(dig - 1, sum - i);

    D[dig][sum] = total;
    return total;
}

ll solve(ll x)
{
    ll total = 0;
    sprintf(cad, "%lld", x);

    int len = strlen(cad);
    int sum = s;
    int quedan = len;

    for (int i = 0; i < len; i++)
    {
        quedan--;
        int curr_digit = cad[i] - '0';

        for (int j = 0; j < curr_digit; j++)
        {
            if (sum - j >= 0)
                total += F(quedan, sum - j);
        }

        sum -= curr_digit;
    }
    return total;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    cin >> a >> b >> s;
    cout << solve(b + 1) - solve(a) << "\n";

    ll ini = a, fin = b;
    while (ini < fin)
    {
        curr_solution = (ini + fin) >> 1;
        ll sol = solve(curr_solution + 1) - solve(ini);
        if (sol)
            fin = curr_solution;
        else
            ini = curr_solution + 1;
    }
    cout << fin << "\n";
    return 0;
}
