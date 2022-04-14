//============================================================================
// Name        : SPOJ ASCDFIB - Ascending Fibonacci Numbers
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Counting sort for sorting a list of fibonacci numbers
//============================================================================

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5;
const int MAXFIB = 1100000 + 5;

int N, digits, a, b, casos, tests = 0;
int fib[MAXFIB];

void fibonacci()
{
    fib[1] = 0;
    fib[2] = 1;
    for (int i = 3; i < MAXFIB; i++)
        fib[i] = (fib[i-1] + fib[i-2]) % MAX;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fibonacci();
    cin >> casos;
    while (casos--) {
        cin >> a >> b;

        int count[MAX] = {0};

        for (int i = 0; i <= b; i++)
            count[fib[a + i]]++;

        int numbers = 0;
        cout << "Case " << ++tests << ":";
        for (int i = 0; i < MAX && numbers < 100; i++) {
            while (count[i] && numbers < 100) {
                cout << " " << i;
                count[i]--;
                numbers++;
            }
        }
        cout << "\n";
    }
    return 0;
}
