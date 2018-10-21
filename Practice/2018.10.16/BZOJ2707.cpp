#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int maxM=1010000;
const int maxScc=105;
const ld eps=1e-8;
const int inf=2147483647;

int n,m,S,T;
vector<int> T1[maxN],T2[maxN],T3[maxN];
int dfncnt,dfn[maxN],low[maxN],scccnt,sccid[maxN],ord[maxN];
int sttop=0,St[maxN],Dg[maxN];
bool ink[maxN];
vector<int> Scc[maxN],Seq;
ld Mat[maxScc][maxScc],E[maxN];
queue<int> Q;

void tarjan(int u);
void Solve(int id);

int main(){
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		if (u!=T) T1[u].push_back(v),T2[v].push_back(u);
	}

	tarjan(S);
	if (dfn[T]==0){
		printf("INF\n");return 0;
	}

	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<sccid[i]<<" ";cout<<endl;

	for (int i=1;i<=n;i++)
		if (dfn[i]!=0)
			for (int j=0,sz=T2[i].size();j<sz;j++)
				if (sccid[i]!=sccid[T2[i][j]])
					T3[sccid[i]].push_back(sccid[T2[i][j]]),++Dg[sccid[T2[i][j]]];

	/*
	for (int i=1;i<=scccnt;i++){
		cout<<i<<":";
		for (int j=0,sz=T3[i].size();j<sz;j++)
			cout<<T3[i][j]<<" ";
		cout<<endl;
	}
	//*/
	
	bool flag=1;
	for (int i=1;i<=scccnt;i++) if ((Dg[i]==0)&&(i!=sccid[T])) {flag=0;break;}
	if (flag==0){
		printf("INF\n");return 0;
	}

	Q.push(sccid[T]);
	do{
		int u=Q.front();Q.pop();
		Solve(u);
		for (int i=0,sz=T3[u].size();i<sz;i++)
			if ((--Dg[T3[u][i]])==0) Q.push(T3[u][i]);
	}
	while (!Q.empty());
	//for (int i=1;i<=n;i++) printf("%.4LF ",E[i]);printf("\n");
	printf("%.3LF\n",E[S]);return 0;
}

void tarjan(int u){
	dfn[u]=low[u]=++dfncnt;ink[u]=1;St[++sttop]=u;
	for (int i=0,sz=T1[u].size();i<sz;i++){
		int v=T1[u][i];
		if (dfn[v]==0){
			tarjan(v);low[u]=min(low[u],low[v]);
		}
		else if (ink[v]) low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]==low[u]){
		int v;scccnt++;
		do sccid[v=St[sttop--]]=scccnt,ink[v]=0,ord[v]=Scc[scccnt].size(),Scc[scccnt].push_back(v);while (v!=u);
	}
	return;
}

void Solve(int id){
	int sz=Scc[id].size();
	for (int i=0;i<sz;i++) for (int j=0;j<sz;j++) Mat[i][j]=(i==j)?(1):(0);
	for (int i=0;i<sz;i++) if (Scc[id][i]!=T) Mat[i][sz]=1;
	for (int i=0;i<sz;i++){
		int u=Scc[id][i];
		for (int j=0,ssz=T1[u].size();j<ssz;j++){
			int v=T1[u][j];
			if (sccid[v]==id) Mat[ord[u]][ord[v]]+=-1.0/(ld)ssz;
			else Mat[ord[u]][sz]+=(ld)E[v]/(ld)ssz;
		}
	}
	for (int i=0;i<sz;i++){
		int now=i;
		for (int j=i+1;j<sz;j++)
			if (fabs(Mat[j][i])>fabs(Mat[now][i])) now=j;
		swap(Mat[now],Mat[i]);
		for (int j=0;j<sz;j++)
			if ((fabs(Mat[j][i])>eps)&&(j!=i)){
				ld d=Mat[j][i]/Mat[i][i];
				for (int k=0;k<=sz;k++) Mat[j][k]=Mat[j][k]-Mat[i][k]*d;
			}
	}
	for (int i=0;i<sz;i++) E[Scc[id][i]]=Mat[i][sz]/Mat[i][i];
	return;
}
/*
6 6 1 6
1 2
1 3
2 4
3 5
4 6
5 6
//*/
