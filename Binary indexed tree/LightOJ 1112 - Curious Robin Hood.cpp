//============================================================================
// Name        : LightOJ 1112 - Curious Robin Hood
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <bits/stdc++.h>
 
using namespace std;
#define MAX 100005
 
int Q, casos, a, b;
int N, fenwick[MAX], number = 1;
int freq[MAX], c;
 
void update(int index, int value)
{
	while (index <= N)
	{
		fenwick[index] += value;
		index += (index & -index);
	}
}
 
int read(int index)
{
	int sum = 0;
	while (index > 0)
	{
		sum += fenwick[index];
		index -= (index & -index);
	}
	return sum;
}
 
int main()
{
	//freopen("C:/Users/Ruben/Desktop/build-ACM/entrada.txt", "r", stdin);
	scanf("%d", &casos);
	while (casos--)
	{
		scanf("%d%d", &N, &Q);
		memset(fenwick, 0, sizeof(fenwick));
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &a);
			freq[i] = a;
			update(i, a);
		}
 
		printf("Case %d:\n", number++);
		for (int i = 0; i < Q; i++)
		{
			scanf("%d", &a);
			if (a == 1)
			{
				scanf("%d", &b);
				printf("%d\n", freq[b + 1]);
				update(b + 1, -freq[b + 1]);
				freq[b + 1] = 0;
			}
			else if (a == 2)
			{
				scanf("%d%d", &b, &c);
				freq[b + 1] += c;
				update(b + 1, c);
			}
			else if (a == 3)
			{
				scanf("%d%d", &b, &c);
				printf("%d\n", read(c + 1) - read(b));
			}
		}
	}
 
	return 0;
}