//============================================================================
// Name        : LightOJ: Points in Segments
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Search
//============================================================================
#define MAX 100005
#define ll long long

#include <bits/stdc++.h>
using namespace std;

int casos, N, Q, a, b;
int points[MAX];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> casos;
    while (casos--)
    {
        cin >> N >> Q;
        for (int i = 0; i < N; i++)
            cin >> points[i];

        while (Q--)
        {
            cin >> a >> b;
            cout << upper_bound(points, points + N, b) - lower_bound(points, points + N, a) << "\n";
        }
    }
    return 0;
}
