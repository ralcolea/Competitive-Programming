//============================================================================
// Name        : LightOJ 1065 - Number Sequence
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Linear recurrence and Matrix Exponentiation
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define ll long long

int casos, a, b, n, m, tests = 1;
const int MOD = 10000;

// Matrix class
template<class T>
class Matrix
{
public:
    int m, n;
    T *data;

    Matrix(int m, int n);
    Matrix(const Matrix<T> &matrix);

    const Matrix<T> &operator=(const Matrix<T> &A);
    const Matrix<T> operator*(const Matrix<T> &A);
    const Matrix<T> operator^(long long P);

    ~Matrix();
};

template<class T>
Matrix<T>::Matrix(int m, int n)
{
    this->m = m;
    this->n = n;
    data = new T[m * n];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &A)
{
    this->m = A.m;
    this->n = A.n;
    data = new T[m * n];
    for( int i = 0; i < m * n; i++ )
        data[i] = A.data[i];
}

template<class T>
Matrix<T>::~Matrix()
{
    delete [] data;
}

template<class T>
const Matrix<T> &Matrix<T>::operator=(const Matrix<T> &A)
{
    if (&A != this)
    {
        delete [] data;
        m = A.m;
        n = A.n;
        data = new T[m * n];
        for (int i = 0; i < m * n; i++)
            data[i] = A.data[i];
    }
    return *this;
}

template<class T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T> &A)
{
    Matrix C(m, A.n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < A.n; ++j)
        {
            C.data[i * C.n + j] = 0;
            for (int k = 0; k < n; ++k)
            {
                T aux = (1LL * data[i * n + k] * A.data[k * A.n + j]) % MOD;
                C.data[i * C.n + j] += aux;
                C.data[i * C.n + j] %= MOD;
            }
        }
    return C;
}

template<class T>
const Matrix<T> Matrix<T>::operator^(long long P)
{
    if (P == 1) return (*this);
    if (P  & 1) return (*this) * ((*this) ^ (P - 1));
    Matrix B = (*this) ^ (P / 2);
    return B * B;
}
// Matrix class

ll compute(int a, int b, int n, int m)
{
    const int remainder = pow(10, m);

    if (n == 0) return a % remainder;
    if (n == 1) return b % remainder;

    /*
     *  F[n] = F[n-1] + F[n-2]
     *
     *  F[0] = a
     *  F[1] = b
     *
            [B]        [M]      [A]
         [  Fn  ]    [1  1]    [Fn-1]
         [ Fn-1 ] =  [1  0] x  [Fn-2]

           F[n] = M^(N-1) * A
    */

    Matrix<long long> M(2,2);
    // initializing matrix
    for (int i = 0; i < M.m * M.n; i++)
        M.data[i] = 0;

    M.data[0] = M.data[1] = M.data[2] = 1;

    n--;
    M = M ^ n;
    return (M.data[0] * b + M.data[1] * a) % remainder;
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> casos;
    while (casos--) {
        cin >> a >> b >> n >> m;
        cout << "Case " << tests++ << ": " << compute(a, b, n, m) << "\n";
    }
    return 0;
}
