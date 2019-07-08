#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=300;
const int maxNN=maxN<<1;
const int maxM=30300*10;
const int inf=1000000000;

class Edge
{
public:
	int v,flow,w;
};

int n,m,K,S,T,Mp[maxN][maxN];
int ecnt=-1,Hd[maxNN],Nt[maxM];
Edge E[maxM];
int Qu[maxNN],Dst[maxNN],inq[maxNN],Flow[maxNN],Path[maxNN];
int C[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool Spfa();
int main()
{
	//freopen("in","r",stdin);
	scanf("%d%d%d",&n,&m,&K);
	memset(Mp,63,sizeof(Mp));
	memset(Hd,-1,sizeof(Hd));
	for (int i=1; i<=n; i++) Mp[i][i]=0;
	for (int i=1; i<=m; i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		Mp[u][v]=min(Mp[u][v],w);
	}
	for (int k=1; k<=n; k++) for (int i=1; i<=n; i++) for (int j=1; j<=n; j++) Mp[i][j]=min(Mp[i][j],Mp[i][k]+Mp[k][j]);
	S=n+n+1;
	T=S+1;
	for (int i=1; i<=n; i++) Add_Edge(S,i,1,0),Add_Edge(i+n,T,1,0);
	for (int i=1; i<=n; i++) for (int j=1; j<=n; j++) if (i!=j&&Mp[i][j]!=Mp[0][0]) Add_Edge(i,j+n,inf,Mp[i][j]);

	for (int i=n-1; i>=0; i--) {
		Spfa();
		C[i]=Dst[T]+C[i+1];
		int now=T;
		while (now!=S) {
			E[Path[now]].flow-=Flow[T];
			E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]^1].v;
		}
	}
	//for (int i=1;i<=n;i++) cout<<C[i]<<" ";cout<<endl;

	while (K--) {
		int c;
		scanf("%d",&c);
		int l=0,r=n,Ans=inf;
		while (l<=r) {
			int mid=(l+r)>>1;
			Ans=min(Ans,mid*c+C[mid]);
			if (mid*c+C[mid]<=(mid+1)*c+C[mid+1]) r=mid-1;
			else l=mid+1;
		}
		//for (int i=0;i<=n;i++) cout<<c*i+C[i]<<" ";cout<<endl;
		printf("%d\n",Ans);
	}
	return 0;
}
void Add_Edge(int u,int v,int flow,int w)
{
	//cout<<"Add:"<<u<<" "<<v<<" "<<flow<<" "<<w<<endl;
	Nt[++ecnt]=Hd[u];
	Hd[u]=ecnt;
	E[ecnt]=((Edge) {
		v,flow,w
	});
	Nt[++ecnt]=Hd[v];
	Hd[v]=ecnt;
	E[ecnt]=((Edge) {
		u,0,-w
	});
	return;
}
bool Spfa()
{
	memset(Dst,63,sizeof(Dst));
	int ql=0,qr=1;
	Qu[1]=S;
	Dst[S]=0;
	Flow[S]=inf;
	while (ql!=qr) {
		++ql;
		ql%=maxNN;
		int u=Qu[ql];
		for (int i=Hd[u]; i!=-1; i=Nt[i])
			if (E[i].flow&&Dst[E[i].v]>Dst[u]+E[i].w) {
				Dst[E[i].v]=Dst[u]+E[i].w;
				Flow[E[i].v]=min(Flow[u],E[i].flow);
				Path[E[i].v]=i;
				if (!inq[E[i].v]) {
					++qr;
					qr%=maxNN;
					Qu[qr]=E[i].v;
					inq[E[i].v]=1;
				}
			}
		inq[u]=0;
	}
	return Dst[T]!=Dst[0];
}