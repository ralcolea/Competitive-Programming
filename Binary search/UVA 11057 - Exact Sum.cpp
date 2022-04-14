//============================================================================
// Name        : UVA 11057 - Exact Sum
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Search
//============================================================================
#include <bits/stdc++.h>
using namespace std;

#define MAX 10005

int N, M, prices[MAX], low, high;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> N)
    {
        for (int i = 0; i < N; i++)
            cin >> prices[i];

        cin >> M;
        low = 0;
        high = 5000001;

        // sorting prices in non-descending order
        sort(prices, prices + N);

        for (int i = 0; i < N - 1 && 2 * prices[i] <= M; i++)
        {
            int index = lower_bound(prices + i + 1, prices + N, M - prices[i]) - prices;
            int a = prices[i];
            int b = prices[index];

            if (a + b == M)
            {
                if (b - a < high - low)
                {
                    low  = a;
                    high = b;
                }
            }
        }
        cout << "Peter should buy books whose prices are " << low << " and " << high << ".\n\n";
    }
    return 0;
}
