//============================================================================
// Name        : LightOJ 1082 - Array Queries
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : SQRT Decomposition to find RMQ
//============================================================================
#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5;
const int INF = 1e9 + 7;
const int MAXSQR = 320;
int n, casos, tests = 0, queries, SQRSize;
int A[MAX], B[MAXSQR], a, b;

int solve(int a, int b) {
    int x = a / SQRSize;
    int y = b / SQRSize;

    int min_value = INF;
    if (x == y) {  // El intervalo está en el mismo bloque
        for (int i = a; i <= b; i++)
            min_value = min(min_value, A[i]);
    }
    else if (x != y) {   // El intervalo está distribuido en varios bloques
        // mínimo del primer bloque parcial
        for (int i = a; i < (x + 1) * SQRSize; i++)
            min_value = min(min_value, A[i]);

        // mínimo de los bloques intermedios
        for (int i = x + 1; i < y; i++)
            min_value = min(min_value, B[i]);

        // mínimo del último bloque parcial
        for (int i = y * SQRSize; i <= b; i++)
            min_value = min(min_value, A[i]);
    }
    return min_value;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> casos;
    while (casos--) {
        cin >> n >> queries;
        SQRSize = sqrt(n) + 1;
        for (int i = 0; i <= SQRSize; i++)
            B[i] = INF;
        for (int i = 0; i < n; i++) {
            cin >> A[i];
            B[i / SQRSize] = min(B[i / SQRSize], A[i]);
        }

        cout << "Case " << ++tests << ":\n";
        while (queries--) {
            cin >> a >> b;
            cout << solve(a-1, b-1) << "\n";
        }
    }
    return 0;
}
