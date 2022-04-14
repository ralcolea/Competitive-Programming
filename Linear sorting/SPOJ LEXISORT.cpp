#include <bits/stdc++.h>
using namespace std;

#define MAX 50000 + 5
#define MAX_ALPHABET_SIZE 255 + 5

int casos, N;
string s[MAX];

void countingSort(int index)
{
    string output[N];
    int count[MAX_ALPHABET_SIZE] = {0}, pos;

    for (int i = 0; i < N; i++)
    {
        pos = s[i][index];
        count[pos]++;
    }

    for (int i = 1; i < MAX_ALPHABET_SIZE; i++)
        count[i] += count[i-1];

    for (int i = N - 1; i >= 0; i--)
    {
        pos = s[i][index];
        output[count[pos] - 1] = s[i];
        count[pos]--;
    }

    for (int i = 0; i < N; i++)
        s[i] = output[i];
}

void radixSort()
{
    int len = s[0].length();
    for (int i = len - 1; i >= 0; i--)
        countingSort(i);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> casos;
    while (casos--)
    {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> s[i];

        radixSort();

        for (int i = 0; i < N; i++)
            cout << s[i] << "\n";
    }
    return 0;
}
