#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define ft first
#define sd second
const int maxN=101000*2;
const int maxM=maxN*8;
const int inf=2000000000;

class Edge{
public:
	int v,flow;
};

int n,m,R,B,SWAP;
int X[maxN],Y[maxN],Eid[maxN];
map<int,int> Idx,Idy,Cdx,Cdy,Mkx,Mky;
map<pair<int,int>,int> Idp;
int nodecnt=0,Sm[maxN];
int ecnt=-1,Hd[maxN],Nt[maxM];
Edge E[maxM];
int Dep[maxN],Qu[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
int Dinic(int S,int T);
bool bfs(int S,int T);
int dfs(int u,int flow,int T);
int main(){
	memset(Hd,-1,sizeof(Hd));
	scanf("%d%d",&n,&m);scanf("%d%d",&R,&B);if (R<B) swap(R,B),SWAP=1;
	for (int i=1;i<=n;i++){
		scanf("%d%d",&X[i],&Y[i]);Idp[mp(X[i],Y[i])]=i;
		++Cdx[X[i]];++Cdy[Y[i]];
		if (Idx[X[i]]==0) Idx[X[i]]=++nodecnt;
		if (Idy[Y[i]]==0) Idy[Y[i]]=++nodecnt;
		Add_Edge(Idx[X[i]],Idy[Y[i]],1);Eid[i]=ecnt-1;
	}
	int S,T,SS,TT;
	S=++nodecnt;T=++nodecnt;SS=++nodecnt;TT=++nodecnt;
	for (int i=1;i<=m;i++){
		int opt,l,d;scanf("%d%d%d",&opt,&l,&d);
		if (opt==1){
			if (Mkx.count(l)) Mkx[l]=min(Mkx[l],d);
			else Mkx[l]=d;
		}
		if (opt==2){
			if (Mky.count(l)) Mky[l]=min(Mky[l],d);
			else Mky[l]=d;
		}
	}
	for (map<int,int>::iterator it=Idx.begin();it!=Idx.end();it++){
		int x=(*it).ft,id=(*it).sd;
		if (Mkx.count(x)){
			int down=max((Cdx[x]-Mkx[x]+1)/2,0),up=(Cdx[x]+Mkx[x])/2;
			if (down>up){
				puts("-1");return 0;
			}
			Add_Edge(S,id,up-down);Sm[S]-=down;Sm[id]+=down;
		}
		else Add_Edge(S,id,inf);
	}
	for (map<int,int>::iterator it=Idy.begin();it!=Idy.end();it++){
		int y=(*it).ft,id=(*it).sd;
		if (Mky.count(y)){
			int down=max((Cdy[y]-Mky[y]+1)/2,0),up=(Cdy[y]+Mky[y])/2;
			if (down>up){
				puts("-1");return 0;
			}
			Add_Edge(id,T,up-down);Sm[id]-=down;Sm[T]+=down;
		}
		else Add_Edge(id,T,inf);
	}
	Add_Edge(T,S,inf);
	int sum=0;
	//for (int i=1;i<=nodecnt;i++) cout<<Sm[i]<<" ";cout<<endl;
	for (int i=1;i<=nodecnt;i++)
		if (Sm[i]>0) Add_Edge(SS,i,Sm[i]),sum+=Sm[i];
		else if (Sm[i]<0) Add_Edge(i,TT,-Sm[i]);

	int cnt=Dinic(SS,TT);
	//cerr<<sum<<" "<<cnt<<endl;
	if (cnt!=sum){
		puts("-1");return 0;
	}
	cnt+=Dinic(S,T);

	//cerr<<cnt<<endl;
	long long Ans=0;
	for (int i=1;i<=n;i++) if (E[Eid[i]].flow) Ans+=R;else Ans+=B;
	printf("%lld\n",Ans);
	for (int i=1;i<=n;i++)
		if (E[Eid[i]].flow^SWAP) printf("r");
		else printf("b");
	puts("");
	return 0;
}
void Add_Edge(int u,int v,int flow){
	//cout<<"Add:"<<u<<" "<<v<<" "<<flow<<endl;
	Nt[++ecnt]=Hd[u];Hd[u]=ecnt;E[ecnt]=((Edge){v,flow});
	Nt[++ecnt]=Hd[v];Hd[v]=ecnt;E[ecnt]=((Edge){u,0});
	return;
}
int Dinic(int S,int T){
	int ret=0;
	while (bfs(S,T)){
		memcpy(cur,Hd,sizeof(cur));
		while (int di=dfs(S,inf,T)) ret+=di;
	}
	return ret;
}
bool bfs(int S,int T){
	memset(Dep,-1,sizeof(Dep));int ql=1,qr=1;Dep[Qu[1]=S]=1;
	while (ql<=qr)
		for (int u=Qu[ql++],i=Hd[u];i!=-1;i=Nt[i])
			if (E[i].flow&&Dep[E[i].v]==-1)
				Dep[Qu[++qr]=E[i].v]=Dep[u]+1;
	return Dep[T]!=-1;
}
int dfs(int u,int flow,int T){
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Nt[i])
		if (E[i].flow&&Dep[E[i].v]==Dep[u]+1){
			int di=dfs(E[i].v,min(flow,E[i].flow),T);
			if (di){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
		}
	return 0;
}
