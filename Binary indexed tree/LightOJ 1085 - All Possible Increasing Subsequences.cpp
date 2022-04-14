    //============================================================================
    // Name        : LightOJ 1085 - All Possible Increasing Subsequences
    // Author      : Rubén Alcolea Núñez
    // Version     : Qt 5.8
    // Copyright   : Your copyright notice
    // Description : Hello World in C++, Ansi-style
    //============================================================================
    #include <bits/stdc++.h>
     
    using namespace std;
    #define MAX 100005
    #define MOD 1000000007
     
    int casos, a, b;
    int N, fenwick[MAX], number = 1;
    int freq[MAX], value;
    set<int> st;
    vector<int> v;
     
    void update(int index, int value)
    {
        while (index <= N)
        {
            fenwick[index] += value;
            fenwick[index] %= MOD;
            index += (index & -index);
        }
    }
     
    int read(int index)
    {
        int sum = 0;
        while (index > 0)
        {
            sum += fenwick[index];
            sum %= MOD;
            index -= (index & -index);
        }
        return sum;
    }
     
    int normalize(int value)
    {
        return lower_bound(v.begin(), v.end(), value) - v.begin() + 1;
    }
     
    int main()
    {
        scanf("%d", &casos);
        while (casos--)
        {
            scanf("%d", &N);
            memset(fenwick, 0, sizeof(fenwick));
            st.clear();
            v.clear();
            for (int i = 1; i <= N; i++)
            {
                scanf("%d", &a);
                freq[i] = a;
                st.insert(a);
            }
     
            for (set<int>::iterator it = st.begin(); it != st.end(); it++)
                v.push_back(*it);
     
            for (int i = 1; i <= N; i++)
            {
                value = normalize(freq[i]);
                update(value, read(value - 1) + 1);
            }
     
            printf("Case %d: %d\n", number++, read(N));
        }
     
        return 0;
    }
     
