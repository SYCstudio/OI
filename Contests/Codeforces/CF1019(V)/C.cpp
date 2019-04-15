#include<bits/stdc++.h>
using namespace std;

const int maxN=1010000;

int n,m;
vector<int> E[maxN];
int vis[maxN];

int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
	int u,v;scanf("%d%d",&u,&v);E[u].push_back(v);
    }
    for (int i=1;i<=n;i++)
	if (vis[i]==0){
	    vis[i]=1;for (int j=0,sz=E[i].size();j<sz;j++) if (!vis[E[i][j]]) vis[E[i][j]]=-1;
	}
    for (int i=n;i>=1;i--)
	if (vis[i]==1) for (int j=0,sz=E[i].size();j<sz;j++) vis[E[i][j]]=-1;
    int cnt=0;for (int i=1;i<=n;i++) if (vis[i]==1) ++cnt;
    printf("%d\n",cnt);for (int i=1;i<=n;i++) if (vis[i]==1) printf("%d ",i);return 0;
}
