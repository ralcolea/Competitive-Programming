//============================================================================
// Name        : UVA 11876 - N + NOD (N)
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Search
//============================================================================
#include <bits/stdc++.h>
using namespace std;

#define MAX 1000005

int casos, a, b, casesNumber = 1;
int last[MAX];
vector<int> sequence;

void sieve()
{
    memset(last, -1, sizeof(last));
    for (int i = 4; i < MAX; i += 2) last[i] = 2;
    for (int i = 3; i * i < MAX; i += 2)
      if (last[i] == -1)
        for (int j = i * i; j < MAX; j += i)
            last[j] = i;
}

int divisors(int N)
{
    if (N == 1)
        return 1;

    int f[30], F = 0;
    int total = 1;
    while (last[N] != -1)
    {
        f[F++] = last[N];
        N /= last[N];
    }
    f[F++] = N;
    sort(f, f + F);
    int curr = 1, i = 1;
    while (i < F)
    {
        if (f[i] == f[i-1]) curr++;
        else
        {
            total *= (curr + 1);
            curr = 1;
        }
        i++;
    }
    total *= (curr + 1);
    return total;
}

void compute()
{
    sieve();
    sequence.push_back(1);
    int current = 1;
    while (sequence[current - 1] < MAX)
    {
        int prev = sequence[current - 1];
        sequence.push_back(prev + divisors(prev));
        current++;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    compute();
    cin >> casos;
    while (casos--)
    {
        cin >> a >> b;
        cout << "Case " << casesNumber++ << ": " <<
                upper_bound(sequence.begin(), sequence.end(), b) -
                lower_bound(sequence.begin(), sequence.end(), a) << "\n";
    }
    return 0;
}
