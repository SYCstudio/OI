#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=310;
const int inf=2147483647;

int n,m;
int Mp[maxN][maxN];
vector<int> T[maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d%d",&n,&m);
		mem(Mp,0);for (int i=1;i<=n;i++) T[i].clear();
		for (int i=1;i<=m;i++){
			int u,v;scanf("%d%d",&u,&v);++u;++v;
			if (Mp[u][v]==0) Mp[u][v]=1,T[u].push_back(v);
		}
		bool flag=1;
		for (int i=1;(i<=n)&&(flag);i++)
			for (int j=0,sz=T[i].size();(j<sz-1)&&(flag);j++){
				int u=T[i][j],v=T[i][j+1];
				for (int k=1;k<=n;k++)
					if (Mp[k][u]^Mp[k][v]){
						flag=0;break;
					}
			}
		printf(flag?"Yes\n":"No\n");
	}
	return 0;
}
