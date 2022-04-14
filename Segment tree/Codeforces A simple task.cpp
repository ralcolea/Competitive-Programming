//==================================================================================
// Contest     : Codeforces Round #312 - Div2 558E:
// Problem     : A simple task
// Author      : Rubén Alcolea Núñez
// Description : DS4: Segment tree + sorting + string
//==================================================================================

#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1e5 + 5;
const int ALPHABET = 26;

int tree[ALPHABET][MAX << 2], lazy[ALPHABET][MAX << 2];
int n, queries, a, b, k, freq[ALPHABET];
string s;

void build(int node = 1, int start = 0, int end = n - 1)
{
    if (start == end) {
        for (int i = 0; i < ALPHABET; i++)
            tree[i][node] = 0;

        tree[s[start] - 'a'][node] = 1;
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node + 0, start, middle);
    build(2 * node + 1, middle + 1, end);

    for (int i = 0; i < ALPHABET; i++)
        tree[i][node] = tree[i][2 * node] + tree[i][2 * node + 1];
}

void update(int index, int node, int value, int start, int end)
{
    lazy[index][node] = value;
    tree[index][node] = (value == 1) * (end - start + 1);
}

void push(int index, int node, int start, int end)
{
    if (lazy[index][node]) {
        if (start != end) {
            int middle = (start + end) / 2;
            update(index, 2 * node + 0, lazy[index][node], start, middle);
            update(index, 2 * node + 1, lazy[index][node], middle + 1, end);
        }
        lazy[index][node] = 0; // lazy is pushed
    }
}

void modify(int index, int a, int b, int value, int node = 1, int start = 0, int end = n - 1)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a) return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b) {
        update(index, node, value, start, end);
        return;
    }

    // pushing lazy propagation
    push(index, node, start, end);

    // otherwise, we split the interval
    int middle = (start + end) / 2;
    modify(index, a, b, value, 2 * node + 0, start, middle);
    modify(index, a, b, value, 2 * node + 1, middle + 1, end);
    tree[index][node] = tree[index][2 * node] + tree[index][2 * node + 1];
}

int query(int index, int a, int b, int node = 1, int start = 0, int end = n - 1)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a) return 0;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
        return tree[index][node];

    // pushing lazy propagation
    push(index, node, start, end);

    // otherwise, we split the interval
    int middle = (start + end) / 2;
    return query(index, a, b, 2 * node + 0, start, middle) +
           query(index, a, b, 2 * node + 1, middle + 1, end);
}

void get_value(int index, int node = 1, int start = 0, int end = n - 1)
{
    // pushing lazy propagation
    push(index, node, start, end);

    if (!tree[index][node]) return;

    if (start == end) {
        s[start] = 'a' + index;
        return;
    }

    // otherwise, we split the interval
    int middle = (start + end) / 2;
    get_value(index, 2 * node + 0, start, middle);
    get_value(index, 2 * node + 1, middle + 1, end);
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> queries;
    cin >> s;
    build(1, 0, n - 1);
    while (queries--) {
        cin >> a >> b >> k;
        a--;   b--;

        // computing frequency and clearing the range
        for (int index = 0; index < ALPHABET; index++) {
            freq[index] = query(index, a, b);
            if (freq[index])
                modify(index, a, b, -1);
        }

        int curr = a;
        if (k == 1) {  // ascending order
            for (int index = 0; index < ALPHABET; index++)
                if (freq[index]) {
                    modify(index, curr, curr + freq[index] - 1, +1);
                    curr += freq[index];
                }
        }
        else if (k == 0) { // descending order
            for (int index = ALPHABET - 1; index >= 0; index--)
                if (freq[index]) {
                    modify(index, curr, curr + freq[index] - 1, +1);
                    curr += freq[index];
                }
        }
    }

    for (int i = 0; i < ALPHABET; i++)
        get_value(i);
    cout << s << "\n";
    return 0;
}