//============================================================================
// Name        : SPOJ - Increasing Subsequences (INCSEQ)
// Author      : Ruben Alcolea
// Version     : Qt 5.8
// Description : Binary indexed tree + DP to count increasing subsequences
//============================================================================
#define MAXN 10005
#define MAXK 55
#define MOD 5000000
 
#include <iterator>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
 
int N, K, value, sol;
int nums[MAXN], temp[MAXN];
 
int dp[MAXN][MAXK], bit[MAXK][MAXN];
 
void update(int index, int k, int value)
{
	while (index < N)
	{
		bit[k][index] += value;
		bit[k][index] %= MOD;
		index += (index & -index);
	}
}
 
int read(int index, int k)
{
	int s = 0;
	while (index > 0)
	{
		s += bit[k][index];
		s %= MOD;
		index -= (index & -index);
	}
 
	return s;
}
 
int main()
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &value);
		nums[i] = temp[i] = value;
	}
 
	// sorting numbers for normalizing
	sort(temp, temp + N);
 
	for (int i = 0; i < N; i++)
	{
		int rank = lower_bound(temp, temp + N, nums[i]) - temp;
		nums[i] = rank + 1;
	}
 
	//dp[i][j]: number of increasing sequences ending at letter i with length j
	for (int i = 0; i < N; i++)
	{
		dp[i][1] = 1;
		update(nums[i], 1, dp[i][1]);
 
		for (int k = 2; k <= K; k++)
		{
			dp[i][k] = read(nums[i] - 1, k - 1);
			update(nums[i], k, dp[i][k]);
		}
 
		sol += dp[i][K];
		sol %= MOD;
	}
 
	printf("%d\n", sol);
	return 0;
} 