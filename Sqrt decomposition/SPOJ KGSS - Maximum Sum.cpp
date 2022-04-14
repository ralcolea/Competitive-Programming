//============================================================================
// Name        : SPOJ KGSS - Maximum Sum
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : SQRT Decomposition to the highest two values of a range with point updates
//============================================================================
#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5;
const int MAXSQR = 320;
int n, SQRSize;
int A[MAX], a, b, queries;
pair<int, int> B[MAXSQR];
char type;

int query(int a, int b) {
    int x = a / SQRSize;
    int y = b / SQRSize;

    pair<int, int> best = make_pair(0, 0);
    if (x == y) {  // El intervalo está en el mismo bloque
        for (int i = a; i <= b; i++) {
            if (A[i] > best.first) {
                best.second = best.first;
                best.first = A[i];
            }
            else if (A[i] > best.second)
                best.second = A[i];
        }
    }
    else if (x != y) {   // El intervalo está distribuido en varios bloques
        // Los dos mayores valores del primer bloque parcial
        for (int i = a; i < (x + 1) * SQRSize; i++)
            if (A[i] > best.first) {
                best.second = best.first;
                best.first = A[i];
            }
            else if (A[i] > best.second)
                best.second = A[i];

        // Los dos mayores valores de los bloques intermedios
        for (int i = x + 1; i < y; i++) {
            auto b = B[i];
            if (b.first > best.first) {
                best.second = max(best.first, b.second);
                best.first = b.first;
            }
            else if (max(b.first, b.second) > best.second)
                best.second = max(b.first, b.second);
        }

        // Los dos mayores valores del útimo bloque parcial
        for (int i = y * SQRSize; i <= b; i++)
            if (A[i] > best.first) {
                best.second = best.first;
                best.first = A[i];
            }
            else if (A[i] > best.second)
                best.second = A[i];
    }
    return best.first + best.second;
}

void update(int pos, int value) {
    int b = pos / SQRSize;
    A[pos] = value;
    // se recorre nuevamente el bloque para recalcular los dos mayores del bloque
    pair<int, int> best = make_pair(0, 0);
    for (int i = b * SQRSize; i < (b + 1) * SQRSize; i++) {
        if (A[i] > best.first) {
            best.second = best.first;
            best.first = A[i];
        }
        else if (A[i] > best.second)
            best.second = A[i];
    }
    // Actualizando el bloque
    B[b] = best;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    // Inicialización
    SQRSize = sqrt(n) + 1;
    for (int i = 0; i <= SQRSize; i++)
        B[i] = make_pair(0, 0);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
        int block = i / SQRSize;
        if (A[i] > B[block].first) {
            B[block].second = B[block].first;
            B[block].first = A[i];
        }
        else if (A[i] > B[block].second)
            B[block].second = A[i];
    }

    cin >> queries;
    while (queries--) {
        cin >> type >> a >> b;
        if (type == 'U')
            update(a-1, b);
        else if (type == 'Q')
            cout << query(a-1, b-1) << "\n";
    }
    return 0;
}
