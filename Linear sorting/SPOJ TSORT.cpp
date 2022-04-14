//============================================================================
// Name        : SPOJ TSORT - Turbo Sort
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Radix sort for sorting a list of integers
//============================================================================
#include <bits/stdc++.h>

using namespace std;
#define MAX 1000005

int N, digits = 1;
int num[MAX];

void countingSort(int power)
{
    int output[N], i, count[10] = {0};

    for (i = 0; i < N; i++)
        count[(num[i] / power) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i-1];

    for (i = N - 1; i >= 0; i--)
    {
        output[count[(num[i] / power) % 10] - 1] = num[i];
        count[(num[i] / power) % 10]--;
    }

    for (i = 0; i < N; i++)
        num[i] = output[i];
}

void radixSort()
{
    for (int i = 1, power = 1; i <= digits; i++, power *= 10)
        countingSort(power);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> num[i];
        int dig = log10(num[i]) + 1;
        digits = max(digits, dig);
    }

    radixSort();
    for (int i = 0; i < N; i++)
        cout << num[i] << "\n";
    return 0;
}