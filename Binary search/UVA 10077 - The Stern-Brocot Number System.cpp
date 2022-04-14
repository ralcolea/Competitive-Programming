//============================================================================
// Name        : UVA 10077: The Stern-Brocot Number System
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Search
//============================================================================
#include <bits/stdc++.h>
using namespace std;

int a, b;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> a >> b;
    while (a != 1 && b != 1)
    {
        pair<int, int> ini = make_pair(0, 1);
        pair<int, int> fin = make_pair(1, 0);
        while (ini != fin)
        {
            pair<int, int> mid = make_pair(ini.first + fin.first, ini.second + fin.second);
            if (a * mid.second == b * mid.first)
                ini = fin;
            else if (a * mid.second < b * mid.first)
            {
                cout << "L";
                fin = mid;
            }
            else if (a * mid.second > b * mid.first)
            {
                cout << "R";
                ini = mid;
            }
        }
        cout << "\n";
        cin >> a >> b;
    }
    return 0;
}
