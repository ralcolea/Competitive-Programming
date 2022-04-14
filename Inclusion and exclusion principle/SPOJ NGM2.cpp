//============================================================================
// Name        : SPOJ NGM2 - Another Game With Numbers
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Inclusion and Exclusion Principle
//============================================================================

#include <bits/stdc++.h>
using namespace std;
#define MAX 20

#define ll long long

int fact[MAX], factors, A;
ll N;

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return (a * b) / gcd(a, b);
}

ll compute(ll R)
{
    ll total = 0;
    factors = A;

    for (int mask = 1; mask < (1 << factors); mask++)
    {
        ll curr = 1;
        int bits = 0;
        for (int i = 0; i < factors; i++)
        {
            if (mask & (1 << i))
            {
                bits++;
                curr = lcm(curr, fact[i]);
            }
        }

        if (bits % 2 == 1)
            total += R / curr;
        else
            total -= R / curr;
    }
    return R - total;
}

int main()
{
    scanf("%lld%d", &N, &A);
    for (int i = 0; i < A; i++)
        scanf("%d", &fact[i]);
    printf("%lld\n", compute(N));
    return 0;
}
