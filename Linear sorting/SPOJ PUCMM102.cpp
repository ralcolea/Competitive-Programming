//============================================================================
// Name        : SPOJ - PUCMM102 - Race Results
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Radix sort for sorting a list of hours with format hh mm ss
//============================================================================
#include <bits/stdc++.h>

using namespace std;
#define MAX 10000 + 5

struct times {
    int hours;
    int minutes;
    int seconds;
    times(int h = 0, int m = 0, int s = 0)
    {
        hours = h;
        minutes = m;
        seconds = s;
    }
    int get(int index)
    {
        switch (index) {
        case 0:
            return seconds;
        case 1:
            return minutes;
        case 2:
            return hours;
        }
        return -1;
    }
} input[MAX];

int N;

void countingSort(int index)
{
    int i, count[100] = {0};
    times output[N];

    for (i = 0; i < N; i++)
        count[input[i].get(index)]++;

    for (i = 1; i < 100; i++)
        count[i] += count[i-1];

    for (i = N - 1; i >= 0; i--)
    {
        output[count[input[i].get(index)] - 1] = input[i];
        count[input[i].get(index)]--;
    }

    for (i = 0; i < N; i++)
        input[i] = output[i];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> input[i].hours >> input[i].minutes >> input[i].seconds;

    countingSort(0);  // Sorting by seconds
    countingSort(1);  // Sorting by minutes
    countingSort(2);  // Sorting by hours

    for (int i = 0; i < N; i++)
        cout << input[i].hours << " " << input[i].minutes << " " << input[i].seconds << "\n";
    return 0;
}