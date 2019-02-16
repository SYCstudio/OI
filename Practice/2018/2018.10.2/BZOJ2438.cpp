#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=301000;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],low[maxN];
int idcnt,Id[maxN],top,St[maxN],Dg[maxN],Sz[maxN];
bool ink[maxN];
vector<int> To[maxN];

void Add_Edge(int u,int v);
void tarjan(int u);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	for (int i=1;i<=n;i++)
		if (dfn[i]==0) tarjan(i);

	for (int i=1;i<=n;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			if (Id[i]!=Id[V[j]]) To[Id[i]].push_back(Id[V[j]]);
	for (int i=1;i<=idcnt;i++){
		sort(To[i].begin(),To[i].end());
		unique(To[i].begin(),To[i].end());
		for (int sz=To[i].size(),j=0;j<sz;j++) ++Dg[To[i][j]];
	}
	int cnt=0;
	for (int i=1,opt=0;i<=idcnt;i++)
		if (Dg[i]==0){
			cnt++;
			if ((Sz[i]==1)&&(opt==0)){
				bool flag=1;
				for (int j=0,sz=To[i].size();j<sz;j++)
					if (Dg[To[i][j]]==1){
						flag=0;break;
					}
				if (flag==1) cnt--,opt=1;
			}
		}
	printf("%.6lf\n",(ld)(n-cnt)/((ld)n));return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void tarjan(int u){
	St[++top]=u;dfn[u]=low[u]=++dfncnt;ink[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (dfn[V[i]]==0){
			tarjan(V[i]);low[u]=min(low[u],low[V[i]]);
		}
		else if (ink[V[i]]) low[u]=min(low[u],dfn[V[i]]);
	if (dfn[u]==low[u]){
		int v;idcnt++;
		do Id[v=St[top--]]=idcnt,ink[v]=0,++Sz[idcnt];while (v!=u);
	}
	return;
}
