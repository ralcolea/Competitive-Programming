//============================================================================
// Name        : Codeforces Round #136 Div 1: B. Little Elephant and Array
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Mo's algorithm
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAXN 100005

int block_size;

struct query
{
    int left, right, index;
    bool operator<(query b) const
    {
        return make_pair(left / block_size, right) <
               make_pair(b.left / block_size, b.right);
    }
    query(int l, int r, int idx)
    {
        left = l;
        right = r;
        index = idx;
    }
};

int n, t, a[MAXN], freq[MAXN], curr_total;
vector<query> q;

void add(int index)
{
    int s = a[index];
    if (s < MAXN)
    {
        freq[s]++;
        curr_total += ( s  == freq[s]);
        curr_total -= (s+1 == freq[s]);
    }
}

void remove(int index)
{
    int s = a[index];
    if (s < MAXN)
    {
        if (freq[s])
        {
            freq[s]--;
            curr_total += ( s  == freq[s]);
            curr_total -= (s-1 == freq[s]);
        }
    }
}

int get_answer()
{
    return curr_total;
}

vector<int> Mo_algorithm(vector<query> queries)
{
    vector<int> ans(queries.size());
    sort(queries.begin(), queries.end());

    // initialize data structure
    curr_total = 0;

    int curr_left  = 0;
    int curr_right = 0;

    // data structure will always reflect the range [curr_left, curr_right]
    for (query q : queries)
    {
        while (curr_left > q.left)
        {
            curr_left--;
            add(curr_left);
        }

        while (curr_right < q.right)
        {
            curr_right++;
            add(curr_right);
        }

        while (curr_left < q.left)
        {
            remove(curr_left);
            curr_left++;
        }

        while (curr_right > q.right)
        {
            remove(curr_right);
            curr_right--;
        }

        ans[q.index] = get_answer();
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	
    cin >> n >> t;
    block_size = sqrt(n) + 1;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    q.clear();
    for (int i = 0; i < t; i++)
    {
        int x, y;
        cin >> x >> y;
        q.push_back(query(x, y, i));
    }

    vector<int> sol = Mo_algorithm(q);
    for (int s : sol)
        cout << s << "\n";
    return 0;
}
