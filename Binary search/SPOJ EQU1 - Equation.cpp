//============================================================================
// Name        : SPOJ EQU1 - Equation
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Search the answer
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define ll long long

int casos, tests = 1;
ll p;

ll binary_search() {
    ll ini = 0;
    ll end = 1e5;

    // f(x) = 3x^2+2x+7
    while (ini < end) {
        ll med = ini + (end - ini) / 2LL;
        ll value = 3LL * med * med + 2LL * med + 7LL;
        if (value < p)
            ini = med + 1;
        else
            end = med;
    }
    return ini;
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> casos;
    while (casos--) {
        cin >> p;
        cout << "Case " << tests++ << ": " << binary_search() << "\n";
    }
    return 0;
}
