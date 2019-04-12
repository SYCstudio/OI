#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=303000;

int n,m;
int ecnt=-1,Hd[maxN],Nt[maxM],V[maxM],Fa[maxN];

void Add_Edge(int u,int v,int w);
void dfs(int u,int fa);
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<n;i++){
	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
}
