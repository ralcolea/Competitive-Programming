//============================================================================
// Name        : UVA 10474 - Where is the Marble
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Search
//============================================================================
#include <bits/stdc++.h>
using namespace std;

#define MAX 100005

int N, Q, num, marbles[MAX], caseNumber = 1;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> Q;
    while (N && Q)
    {
        for (int i = 0; i < N; i++)
            cin >> marbles[i];
        sort(marbles, marbles + N);
        cout << "CASE# " << caseNumber++ << ":\n";
        while (Q--)
        {
            cin >> num;
            int pos = lower_bound(marbles, marbles + N, num) - marbles;
            if (marbles[pos] == num)
                cout << num << " found at " << pos + 1 << "\n";
            else
                cout << num << " not found" << "\n";
        }
        cin >> N >> Q;
    }
    return 0;
}