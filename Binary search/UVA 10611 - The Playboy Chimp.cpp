//============================================================================
// Name        : UVA 10611 - The Playboy Chimp
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Search
//============================================================================
#include <bits/stdc++.h>
using namespace std;

#define MAX 50005

int N, Q, num, heights[MAX];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> heights[i];
    cin >> Q;
    while (Q--)
    {
        cin >> num;
        int pos = lower_bound(heights, heights + N, num) - heights - 1;
        if (heights[0] >= num)
            cout << "X" << " ";
        else if (heights[pos] < num)
            cout << heights[pos] << " ";

        pos = upper_bound(heights, heights + N, num) - heights;
        if (pos < N)
            cout << heights[pos] << "\n";
        else
            cout << "X\n";
    }
    return 0;
}
