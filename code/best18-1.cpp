#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=10;
const int inf=2147483647;

int n,m,K;
int M[maxN],Cnt[1<<maxM];
char Input[maxM];

int main()
{
	int TTT;scanf("%d",&TTT);
	for (int ti=1;ti<=TTT;ti++){
		scanf("%d%d%d",&n,&m,&K);mem(M,0);
		for (int i=1;i<=n;i++){
			scanf("%s",Input);
			for (int j=0;j<m;j++)
				if (Input[j]=='B') M[i]|=(1<<j);
		}

		int Ans=0;
		for (int S=0;S<(1<<m);S++){
			mem(Cnt,0);
			int tot=0;
			for (int i=1;i<=n;i++){
				int SS=(M[i]|S)^S;
				tot=tot+i-1-Cnt[SS];Cnt[SS]++;
			}
			if (tot>=K) Ans++;
		}

		printf("Case #%d: %d\n",ti,Ans);
	}
	return 0;
}
