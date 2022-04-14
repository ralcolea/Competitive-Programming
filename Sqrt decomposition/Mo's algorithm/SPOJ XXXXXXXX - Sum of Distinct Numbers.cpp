//==================================================================================
// Name        : SPOJ: XXXXXXXX - Sum of Distinct Numbers
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Mo's algorithm with updates + coordinate compression
//==================================================================================
 
#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 5e5 + 5;
const int MAX = 15e4;
typedef long long ll;
 
int n, queries, current_time;
int A[MAXN + 5];
int freq[MAX];
int hashMap[MAX];
ll sum;
int block_size;
 
struct Query
{
	int left, right, current_time, index;
	bool operator<(Query b) const
	{
		if (left / block_size != b.left / block_size)
			return left / block_size < b.left / block_size;
 
		if (right / block_size != b.right / block_size)
			return right / block_size < b.right / block_size;
 
		return current_time < b.current_time;
	}
 
	Query(int l, int r, int time, int idx)
	{
		left = l;
		right = r;
		current_time = time;
		index = idx;
	}
};
 
struct Update
{
	int index;
	int value;
 
	Update(int idx, int v)
	{
		index = idx;
		value = v;
	}
};
 
vector<Query>  q;
vector<Update> u;
 
void add(int value)
{
	freq[value]++;
	if (freq[value] == 1)
		sum += hashMap[value];
}
 
void remove(int value)
{
	freq[value]--;
	if (freq[value] == 0)
		sum -= hashMap[value];
}
 
void applyUpdate(int pos, int left, int right)
{
	int index = u[pos].index;
	int curr_value = u[pos].value;
	int prev_value = A[index];
	A[index] = curr_value;
	u[pos].value = prev_value;
 
	// Si la posición está en el rango actual, se actualiza la suma total
	if (left <= index && index <= right)
	{
		// Eliminar el valor anterior
		remove(prev_value);
 
		// Adicionar el valor actual
		add(curr_value);
	}
}
 
vector<ll> Mo_algorithm(vector<Query> queries)
{
	vector<ll> ans(queries.size());
	sort(queries.begin(), queries.end());
 
	// initialize data structure
	sum = 0;
 
	int curr_left  =  1;
	int curr_right =  0;
 
	// data structure will always reflect the range [curr_left, curr_right]
	current_time = 0;
	for (Query q : queries)
	{
		while (current_time < q.current_time)
		{
			applyUpdate(current_time, curr_left, curr_right);
			current_time++;
		}
 
		while (current_time > q.current_time)
		{
			current_time--;
			applyUpdate(current_time, curr_left, curr_right);
		}
 
		while (curr_left > q.left)
		{
			curr_left--;
			add(A[curr_left]);
		}
 
		while (curr_right < q.right)
		{
			curr_right++;
			add(A[curr_right]);
		}
 
		while (curr_left < q.left)
		{
			remove(A[curr_left]);
			curr_left++;
		}
 
		while (curr_right > q.right)
		{
			remove(A[curr_right]);
			curr_right--;
		}
 
		// Actualizando la respuesta de la consulta
		ans[q.index] = sum;
	}
	return ans;
}
 
void coordinate_compression()
{
	map<int, int> M;
	for (int i = 1; i <= n; i++)
		M[A[i]] = 0;
 
	// Adicionando los valores de los updates al mapa
	for (auto i : u)
		M[i.value] = 0;
 
	int rank = 1;
	for (auto it = M.begin(); it != M.end(); it++)
	{
		it->second = rank++;
		hashMap[rank - 1] = it->first;
	}
 
	for (int i = 1; i <= n; i++)
		A[i] = M[A[i]];
 
	// Normalizando los valores de los updates
	for (size_t i = 0; i < u.size(); i++)
		u[i].value = M[u[i].value];
}
 
int main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n;
	block_size = cbrt(n * n);
	for (int i = 1; i <= n; i++)
		cin >> A[i];
 
	q.clear();
	u.clear();
	current_time = 0;
	int queriesNumber = 0;
	cin >> queries;
	for (int i = 0; i < queries; i++)
	{
		int a, b;
		char op;
		cin >> op >> a >> b;
		if (op == 'Q')
			q.push_back(Query(a, b, current_time, queriesNumber++));
		else if (op == 'U')
		{
			u.push_back(Update(a, b));
			current_time++;
		}
	}
 
	coordinate_compression();
 
	vector<ll> sol = Mo_algorithm(q);
	for (ll s : sol)
		cout << s << "\n";
 
	return 0;
} 