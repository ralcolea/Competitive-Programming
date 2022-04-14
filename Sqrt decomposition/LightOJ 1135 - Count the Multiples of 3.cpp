//============================================================================
// Name        : LightOJ 1135 - Count the Multiples of 3
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : SQRT Decomposition to find multiples of 3 in ranges with updates
//============================================================================
#include <bits/stdc++.h>

using namespace std;

struct Block {
    int mod0;
    int mod1;
    int mod2;
    int sum;

    Block() {
        mod0 = mod1 = 0;
        mod2 = sum = 0;
    }
};

const int MAX = 1e5 + 5;
const int MAXSQR = 320;
int n, casos, tests = 0, SQRSize;
int A[MAX], a, b, type, queries;
Block B[MAXSQR];

int queryBlock(int b)
{
    switch(B[b].sum % 3)
    {
        case 0: return B[b].mod0;
        case 1: return B[b].mod2;
        case 2: return B[b].mod1;
    }

    return B[b].mod0;
}

int query(int a, int b) {
    int x = a / SQRSize;
    int y = b / SQRSize;

    int multiples3 = 0;
    if (x == y) {  // El intervalo está en el mismo bloque
        for (int i = a; i <= b; i++)
            multiples3 += ((A[i] + B[i / SQRSize].sum) % 3 == 0);
    }
    else if (x != y) {   // El intervalo está distribuido en varios bloques
        // cantidad de múltiplos de 3 del primer bloque parcial
        for (int i = a; i < (x + 1) * SQRSize; i++)
            multiples3 += ((A[i] + B[i / SQRSize].sum) % 3 == 0);

        // cantidad de múltiplos de 3 de los bloques intermedios
        for (int i = x + 1; i < y; i++)
            multiples3 += queryBlock(i);

        // cantidad de múltiplos de 3 del útimo bloque parcial
        for (int i = y * SQRSize; i <= b; i++)
            multiples3 += ((A[i] + B[i / SQRSize].sum) % 3 == 0);
    }
    return multiples3;
}

void updateBlock(int index, int value) {
    int b = index / SQRSize;

    if (A[index] % 3 == 0) B[b].mod0 += value;
    else if (A[index] % 3 == 1) B[b].mod1 += value;
    else if (A[index] % 3 == 2) B[b].mod2 += value;
}

void update(int a, int b) {
    int x = a / SQRSize;
    int y = b / SQRSize;

    if (x == y) {
        for (int i = a; i <= b; i++) {
            updateBlock(i, -1);
            A[i]++;
            updateBlock(i, +1);
        }
    }
    else if (x != y) {
        // actualizar cantidad de múltiplos de 3 del primer bloque parcial
        for (int i = a; i < (x + 1) * SQRSize; i++) {
            updateBlock(i, -1);
            A[i]++;
            updateBlock(i, +1);
        }

        // actualizar suma acumulada de los bloques intermedios
        for (int i = x + 1; i < y; i++)
            B[i].sum++;

        // actualizar cantidad de múltiplos de 3 del último bloque parcial
        for (int i = y * SQRSize; i <= b; i++) {
            updateBlock(i, -1);
            A[i]++;
            updateBlock(i, +1);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> casos;
    while (casos--) {
        cin >> n >> queries;
        // Inicialización
        SQRSize = sqrt(n) + 1;
        for (int i = 0; i <= SQRSize; i++)
            B[i] = Block();

        for (int i = 0; i < n; i++) {
            A[i] = 0;
            B[i / SQRSize].mod0++;
        }

        cout << "Case " << ++tests << ":\n";
        while (queries--) {
            cin >> type >> a >> b;
            if (type == 0)
                update(a, b);
            else if (type == 1)
                cout << query(a, b) << "\n";
        }
    }
    return 0;
}
