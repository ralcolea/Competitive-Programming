//============================================================================
// Name        : UVA 12086 - Potentiometers
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : SQRT Decomposition to solve range sum problem
//============================================================================
#include <bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 5;
const int MAXSQR = 455;
int n, tests = 0, SQRSize;
int A[MAX], B[MAXSQR], a, b;
string s;

int query(int a, int b) {
    int x = a / SQRSize;
    int y = b / SQRSize;

    int sum = 0;
    if (x == y) {  // El intervalo está en el mismo bloque
        for (int i = a; i <= b; i++)
            sum += A[i];
    }
    else if (x != y) {   // El intervalo está distribuido en varios bloques
        // suma de los elementos del primer bloque parcial
        for (int i = a; i < (x + 1) * SQRSize; i++)
            sum += A[i];

        // mínimo de los bloques intermedios
        for (int i = x + 1; i < y; i++)
            sum += B[i];

        // suma de los elementos del primer bloque parcial
        for (int i = y * SQRSize; i <= b; i++)
            sum += A[i];
    }
    return sum;
}

void update(int x, int value) {
    B[x / SQRSize] += (value - A[x]);
    A[x] = value;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    while (n) {
        SQRSize = sqrt(n) + 1;
        for (int i = 0; i <= SQRSize; i++)
            B[i] = 0;

        for (int i = 0; i < n; i++) {
            cin >> A[i];
            B[i / SQRSize] += A[i];
        }

        cin >> s;
        cout << "Case " << ++tests << ":\n";
        while (s[0] != 'E') {
            if (s[0] == 'M') {
                cin >> a >> b;
                cout << query(a-1, b-1) << "\n";
            }
            else if (s[0] == 'S') {
                cin >> a >> b;
                update(a-1, b);
            }
            cin >> s;
        }
        cin >> n;
        if (n) cout << "\n";
    }
    return 0;
}
