//============================================================================
// Name        : UVA 374 - Big Mod
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Fast Modular Exponentiation
//============================================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll b, p, m;

ll solve(ll b, ll p) {
    if (p == 0LL)
        return 1;

    if (p & 1)
        return (b * solve(b, p - 1)) % m;

    ll s = solve(b, p / 2LL) % m;
    return (s * s) % m;
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    while (cin >> b >> p >> m) {
        cout << solve(b % m, p) << "\n";
    }
    return 0;
}
