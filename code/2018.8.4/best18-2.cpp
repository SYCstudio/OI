#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxAlpha=26;
const int inf=2147483647;

int n,Q;
int Cnt[maxAlpha][maxN];
char Input[maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	for (int ti=1;ti<=TTT;ti++){
		printf("Case #%d:\n",ti);
		scanf("%d%d",&n,&Q);mem(Cnt,0);
		scanf("%s",Input+1);
		for (int i=1;i<=n;i++){
			for (int j=0;j<maxAlpha;j++) Cnt[j][i]=Cnt[j][i-1];
			Cnt[Input[i]-'A'][i]++;
		}

		while (Q--){
			int l,r;scanf("%d%d",&l,&r);
			int id=0;
			for (id=0;id<maxAlpha;id++) if (Cnt[id][r]-Cnt[id][l-1]) break;
			printf("%d\n",Cnt[id][r]-Cnt[id][l-1]);
		}
	}
	return 0;
}
