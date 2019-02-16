#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=101000*2;
const int inf=2147483647;

class Limit
{
public:
	int opt,a,b;
};

class Edge
{
public:
	int v,w;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
Limit In[maxM];
int dfncnt,dfn[maxN],low[maxN],top,St[maxN],idcnt,Id[maxN],Size[maxN],Mx[maxN],Dg[maxN];
vector<Edge> E[maxN];
queue<int> Q;
bool ink[maxN];

void Add_Edge(int u,int v);
void tarjan(int u);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&In[i].opt,&In[i].a,&In[i].b);
		if (In[i].opt==1) Add_Edge(In[i].a,In[i].b),Add_Edge(In[i].b,In[i].a);
		if (In[i].opt==3) Add_Edge(In[i].b,In[i].a);
		if (In[i].opt==5) Add_Edge(In[i].a,In[i].b);
	}
	for (int i=1;i<=n;i++)
		if (dfn[i]==0) tarjan(i);
	//for (int i=1;i<=n;i++) cout<<Id[i]<<" ";cout<<endl;

	bool flag=1;
	for (int i=1;i<=m;i++){
		int u=Id[In[i].a],v=Id[In[i].b];
		//cout<<i<<" "<<In[i].opt<<" "<<u<<" "<<v<<endl;
		if (In[i].opt==2){
			if (u==v){flag=0;break;}
			E[u].push_back((Edge){v,1});
		}
		if ((In[i].opt==3)&&(u!=v)) E[v].push_back((Edge){u,0});
		if (In[i].opt==4){
			if (u==v) {flag=0;break;}
			E[v].push_back((Edge){u,1});
		}
		if ((In[i].opt==5)&&(u!=v)) E[u].push_back((Edge){v,0});
	}
	if (flag==0){
		printf("-1\n");return 0;
	}

	for (int i=1;i<=idcnt;i++){
		Mx[i]=0;
		for (int j=0,sz=E[i].size();j<sz;j++)
			Dg[E[i][j].v]++;
	}
	//for (int i=1;i<=idcnt;i++) cout<<Dg[i]<<" ";cout<<endl;
	for (int i=1;i<=idcnt;i++)
		if (Dg[i]==0){
			Mx[i]=1;Q.push(i);
		}
	int ncnt=0;
	while (!Q.empty()){
		ncnt++;int u=Q.front();Q.pop();
		for (int i=0,sz=E[u].size();i<sz;i++){
			int v=E[u][i].v;
			Mx[v]=max(Mx[v],Mx[u]+E[u][i].w);
			if ((--Dg[v])==0) Q.push(v);
		}
	}

	if (ncnt!=idcnt) printf("-1\n");
	else{
		ll Ans=0;
		for (int i=1;i<=idcnt;i++) Ans=Ans+1ll*Size[i]*Mx[i];
		printf("%lld\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void tarjan(int u){
	St[++top]=u;dfn[u]=low[u]=++dfncnt;ink[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (dfn[V[i]]==0){
			tarjan(V[i]);
			low[u]=min(low[u],low[V[i]]);
		}
		else if (ink[V[i]]) low[u]=min(low[u],dfn[V[i]]);
	if (dfn[u]==low[u]){
		int v;idcnt++;
		do Size[Id[v=St[top--]]=idcnt]++,ink[v]=0;
		while (v!=u);
	}
	return;
}
