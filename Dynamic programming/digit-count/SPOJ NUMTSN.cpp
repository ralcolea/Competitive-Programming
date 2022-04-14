//============================================================================
// Name          : SPOJ NUMTSN - 369 Numbers
// Author        : Rubén Alcolea Núñez
// Classification: Dynamic Programming
// Description   : Digit DP
//============================================================================
#include <iostream>
#include <cstring>

using namespace std;

#define MAX 60
#define MOD 1000000007
#define ll long long

bool mem[MAX][MAX][MAX][MAX];
ll dp[MAX][MAX][MAX][MAX];

int queries, x, y, casos;
char a[MAX], b[MAX];

void reverse(char x[MAX])
{
    int i = 0;
    int j = strlen(x) - 1;
    while (i < j)
    {
        swap(x[i], x[j]);
        i++;   j--;
    }
}

void increase(char x[MAX])
{
    int len = strlen(x);
    reverse(x);
    int carry = 1, cursor = 0;
    while (carry > 0 && cursor < len)
    {
        int s = (x[cursor] - '0') + carry;
        carry = s / 10;
        x[cursor] = (s % 10) + '0';
        cursor++;
    }

    if (carry)
    {
        x[cursor++] = carry + '0';
        x[cursor] = '\0';
    }

    // reversing the string
    reverse(x);
}

ll F(int digits, int three, int six, int nine)
{
    if (digits == 0)
        return (three == six && six == nine && three >= 1);

    if (mem[digits][three][six][nine])
        return dp[digits][three][six][nine];

    mem[digits][three][six][nine] = true;

    ll ret = 0LL;
    for (int i = 0; i <= 9; i++)
    {
        ret += F(digits - 1, three + (i == 3), six + (i == 6), nine + (i == 9));
        ret %= MOD;
    }

    dp[digits][three][six][nine] = ret;
    return ret;
}

ll solve(char x[MAX])
{
    int len = strlen(x);
    int remain = len;

    ll ret = 0;
    int curr_three = 0, curr_six = 0, curr_nine = 0;
    for (int i = 0; i < len; i++)
    {
        remain--;
        int d = x[i] - '0';

        for (int j = 0; j < d; j++)
        {
            ret += F(remain, curr_three + (j == 3), curr_six + (j == 6), curr_nine + (j == 9));
            ret %= MOD;
        }

        curr_three += (d == 3);
        curr_six   += (d == 6);
        curr_nine  += (d == 9);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //freopen("../build-ACM/entrada.txt", "r", stdin);
    cin >> queries;
    while (queries--)
    {
        cin >> a >> b;
        increase(b);
        cout << (solve(b) + MOD - solve(a)) % MOD << "\n";
    }
    return 0;
}
