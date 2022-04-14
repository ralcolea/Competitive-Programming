//============================================================================
// Name        : SPOJ - YODANESS
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAX 30005

#define ll long long
#define endl '\n'

int casos, N;
ll fenwick[MAX], inversions;
string c[MAX], x;
map<string, int> h;

ll read(int index, ll tree[MAX])
{
    ll sum = 0;
    while (index)
    {
        sum += tree[index];
        index -= (index & -index);
    }

    return sum;
}

void update(ll value, int index, ll tree[MAX])
{
    while (index <= N)
    {
        tree[index] += value;
        index += (index & -index);
    }
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> casos;
    while (casos--)
    {
        cin >> N;

        for (int i = 1; i <= N; i++)
            cin >> c[i];

        h.clear();
        for (int i = 1; i <= N; i++)
        {
            cin >> x;
            h.insert(make_pair(x, i));
        }

        // initializing fenwick for next test case
        for (int i = 1; i <= N; i++)
            fenwick[i] = 0;

        inversions = 0;
        for (int i = 1; i <= N; i++)
        {
            int index = h[c[i]];
            int numbers = read(index, fenwick);

            if (numbers)
                inversions += numbers;

            update(+1, 1, fenwick);
            update(-1, index + 1, fenwick);
        }

        cout << inversions << endl;
    }
    return 0;
}
