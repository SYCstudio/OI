#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=101000;
const int maxM=1010000<<1;

int n,m;
int ecnt=-1,Hd[maxN],Nt[maxM],V[maxM],Dg[maxN];
int vis[maxN],vism[maxM];
int eucnt,Eular[maxM],top,St[maxM],inst[maxN];
int Ans[maxM],Lf[maxN],Rh[maxN];

void Add_Edge(int u,int v);
void dfs(int u);
int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	memset(Hd,-1,sizeof(Hd));
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) {
		int u,v,a,b;
		scanf("%d%d%d%d",&u,&v,&a,&b);
		if (a!=b) Add_Edge(u,v);
	}
	for (int i=1; i<=n; i++)
		if (Dg[i]&1) {
			puts("NIE");
			return 0;
		}

	for (int i=1; i<=n; i++) if (!vis[i]) dfs(i);

	//for (int i=1;i<=eucnt;i++) cout<<Eular[i]<<" ";cout<<endl;
	//cerr<<eucnt<<endl;
	reverse(&Eular[1],&Eular[eucnt+1]);
	int cnt=0,seqcnt=0;
	for (int i=1; i<=eucnt; i++)
		if (inst[Eular[i]]==1) {
			++cnt;
			Lf[cnt]=seqcnt+1;
			Ans[++seqcnt]=Eular[i];
			while (top&&St[top]!=Eular[i]) --inst[St[top]],Ans[++seqcnt]=St[top--];
			Ans[++seqcnt]=Eular[i];
			Rh[cnt]=seqcnt;
		} else {
			++inst[Eular[i]];
			St[++top]=Eular[i];
		}

	printf("%d\n",cnt);
	for (int i=1; i<=cnt; i++) {
		printf("%d ",Rh[i]-Lf[i]);
		for (int j=Lf[i]; j<=Rh[i]; j++) printf("%d ",Ans[j]);
		puts("");
	}

	return 0;
}
void Add_Edge(int u,int v)
{
	Nt[++ecnt]=Hd[u];
	Hd[u]=ecnt;
	V[ecnt]=v;
	Nt[++ecnt]=Hd[v];
	Hd[v]=ecnt;
	V[ecnt]=u;
	++Dg[u];
	++Dg[v];
	return;
}
void dfs(int u)
{
	vis[u]=1;
	for (int &i=Hd[u]; i!=-1; i=Nt[i]) {
		if (vism[i]||vism[i^1]) continue;
		vism[i]=vism[i^1]=1;
		dfs(V[i]);
	}
	Eular[++eucnt]=u;
	return;
}
