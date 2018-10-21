#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30;
const int inf=2147483647;

int n,SG[maxN*maxN];
bool vis[maxN*maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d",&n);mem(SG,0);
		for (int i=n-1;i>=0;i--){
			mem(vis,0);
			for (int j=i+1;j<=n;j++)
				for (int k=j;k<=n;k++)
					vis[SG[j]^SG[k]]=1;
			while (vis[SG[i]]) SG[i]++;
		}

		int sum=0;
		for (int i=1;i<=n;i++){
			int key;scanf("%d",&key);
			if (key&1) sum^=SG[i];
		}

		if (sum==0){
			printf("-1 -1 -1\n0\n");continue;
		}
		int cnt=0,A=0,B=0,C=0;
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				for (int k=j;k<=n;k++)
					if ((sum^SG[i]^SG[j]^SG[k])==0)
						if (++cnt==1) A=i-1,B=j-1,C=k-1;
		printf("%d %d %d\n%d\n",A,B,C,cnt);
	}
	return 0;
}
