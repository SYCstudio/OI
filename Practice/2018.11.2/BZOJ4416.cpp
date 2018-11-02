#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500;
const int maxAlpha=26;
const int inf=2147483647;

int n,K;
char Input[maxN];
int F[1<<22],Next[maxAlpha][maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d",&K);scanf("%s",Input+1);n=strlen(Input+1);
		if (K>=22){
			printf("NO\n");continue;
		}
		mem(F,0);mem(Next,0);
		for (int i=1;i<=n;i++){
			for (int j=i-1;j>=0;j--)
				if (Next[Input[i]-'a'][j]==0) Next[Input[i]-'a'][j]=i;
				else break;
		}
		bool flag=1;
		for (int S=0;S<(1<<K)-1;S++){
			int now=F[S];
			for (int i=0;i<K;i++)
				if ((S&(1<<i))==0){
					if (Next[i][now]==0){
						flag=0;break;
					}
					F[S|(1<<i)]=max(F[S|(1<<i)],Next[i][now]);
				}
			if (flag==0) break;
		}
		if (flag==0) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
