//============================================================================
// Name        : UVA 11621 - Small Factors
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Search
//============================================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll M;
vector<ll> factors;

void build()
{
    factors.push_back(2);
    factors.push_back(3);

    int current = 0;
    while (factors[current] * 2 <= 1LL << 31LL)
    {
        ll curr = factors[current++];
        factors.push_back(2LL * curr);
        factors.push_back(3LL * curr);
    }

    sort(factors.begin(), factors.end());
    factors.resize(unique(factors.begin(), factors.end()) - factors.begin());
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    build();
    cin >> M;
    while (M)
    {
        cout << *lower_bound(factors.begin(), factors.end(), M) << "\n";
        cin >> M;
    }
    return 0;
}
