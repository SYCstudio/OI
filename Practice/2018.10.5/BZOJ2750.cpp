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

const int maxN=1510;
const int maxM=5010;
const int Mod=1000000007;
const int inf=2147483647;

class HData
{
public:
	int u,key;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Dist[maxN],Ans[maxM],F1[maxN],F2[maxN],D1[maxN],D2[maxN];
bool vis[maxN];
priority_queue<HData> H;
vector<int> T1[maxN],T2[maxN];
queue<int> Q;

void Add_Edge(int u,int v,int w);
void Do(int u);
bool operator < (HData A,HData B);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);
	}

	for (int i=1;i<=n;i++) Do(i);

	for (int i=1;i<=m;i++) printf("%d\n",Ans[i]);return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void Do(int S){
	//cout<<"Do:"<<S<<endl;
	for (int i=1;i<=n;i++) Dist[i]=inf;while (!H.empty()) H.pop();mem(vis,0);
	Dist[S]=0;H.push((HData){S,0});
	do{
		int u=H.top().u;H.pop();
		if (vis[u]) continue;vis[u]=1;
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((vis[V[i]]==0)&&(Dist[V[i]]>Dist[u]+W[i])){
				Dist[V[i]]=Dist[u]+W[i];
				H.push((HData){V[i],Dist[V[i]]});
			}
	}
	while (!H.empty());

	mem(D1,0);mem(D2,0);for (int i=1;i<=n;i++) T1[i].clear(),T2[i].clear();
	for (int i=1;i<=n;i++)
		if (Dist[i]!=inf)
			for (int j=Head[i];j!=-1;j=Next[j])
				if (Dist[V[j]]==Dist[i]+W[j]) T1[i].push_back(V[j]),++D1[V[j]],T2[V[j]].push_back(i),++D2[i];

	mem(F1,0);mem(F2,0);
	while (!Q.empty()) Q.pop();
	F1[S]=1;Q.push(S);
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		for (int i=0,sz=T1[u].size();i<sz;i++){
			F1[T1[u][i]]=(F1[T1[u][i]]+F1[u])%Mod;
			if ((--D1[T1[u][i]])==0) Q.push(T1[u][i]);
		}
	}
	for (int i=1;i<=n;i++) if ((Dist[i]!=inf)&&(D2[i]==0)) Q.push(i);
	while (!Q.empty()){
		int u=Q.front();Q.pop();F2[u]=(F2[u]+1)%Mod;
		for (int i=0,sz=T2[u].size();i<sz;i++){
			F2[T2[u][i]]=(F2[T2[u][i]]+F2[u])%Mod;
			if ((--D2[T2[u][i]])==0) Q.push(T2[u][i]);
		}
	}
	for (int i=1;i<=n;i++)
		if (Dist[i]!=inf)
			for (int j=Head[i];j!=-1;j=Next[j])
				if (Dist[V[j]]==Dist[i]+W[j]) Ans[j]=(Ans[j]+1ll*F1[i]*F2[V[j]]%Mod)%Mod;

	//for (int i=1;i<=n;i++) cout<<Dist[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<F1[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<F2[i]<<" ";cout<<endl;
	return;
}

bool operator < (HData A,HData B){
	return A.key>B.key;
}
