//============================================================================
// Name        : SPOJ SBANK - Sorting Bank Accounts
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Counting sort for sorting a list of bank accounts
//============================================================================
#include <bits/stdc++.h>

using namespace std;

int n, casos;
map<string, int> hashMap;
string s1, s2, s3, s4, s5, s6;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> casos;
    while (casos--) {
        hashMap.clear();
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> s1 >> s2 >> s3 >> s4 >> s5 >> s6;
            string s = s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5 + " " + s6;

            if (hashMap.find(s) != hashMap.end())
                hashMap[s]++;
            else
                hashMap[s] = 1;
        }

        for (auto curr = hashMap.begin(); curr != hashMap.end(); curr++)
            cout << curr->first << " " << curr->second << "\n";
        cout << "\n";
    }
    return 0;
}
