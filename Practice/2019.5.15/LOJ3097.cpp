#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cassert>
using namespace std;

#define ft first
#define sd second
#define mp make_pair
typedef long long ll;
const int maxN=1010;
const int maxBit=14;
const int maxNN=maxN*(2+maxBit);
const int maxMM=maxNN*8;
const int inf=2000000000;

class Edge
{
public:
	int v,flow;
	ll w;
};

int n,W,S,T,ncnt;
int ecnt=-1,Hd[maxNN],Nt[maxMM];
Edge E[maxMM];
pair<int,int> Dt[maxN];
ll D[maxNN];
int Path[maxNN];

void Add_Edge(int u,int v,int flow,int w);
void Divide(int l,int r);
bool spfa();
int main()
{
	memset(Hd,-1,sizeof(Hd));
	scanf("%d%d",&n,&W);
	for (int i=1; i<=n; i++) scanf("%d",&Dt[i].ft),Dt[i].sd=i;
	ncnt=n+n;
	S=++ncnt;
	T=++ncnt;
	for (int i=1; i<=n; i++) Add_Edge(S,i,1,0),Add_Edge(i+n,T,1,0),Add_Edge(i,T,1,W);
	//for (int i=1;i<=n;i++) for (int j=i+1;j<=n;j++) Add_Edge(j,i+n,1,abs(Dt[i].ft-Dt[j].ft));
	Divide(1,n);
	/*
	for (int i=1;i<=ncnt;i++)
	for (int j=Hd[i];j!=-1;j=Nt[j])
	    if (E[j].flow) cout<<i<<" "<<E[j].v<<" "<<E[j].w<<endl;
	//*/

	ll Ans=0;
	while (spfa()) {
		int now=T;
		Ans+=D[T];
		//cout<<D[T]<<endl;
		while (now!=S) {
			//cout<<now<<" ";
			--E[Path[now]].flow;
			++E[Path[now]^1].flow;
			now=E[Path[now]^1].v;
		}//cout<<S<<endl;
	}
	printf("%lld\n",Ans);
	return 0;
}
void Add_Edge(int u,int v,int flow,int w)
{
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
void Divide(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	Divide(l,mid);
	Divide(mid+1,r);
	for (int i=l,j=1; i<=mid; i++,j++) Add_Edge(ncnt+j,Dt[i].sd+n,inf,0);
	for (int i=l,j=1; i<mid; i++,j++) {
		Add_Edge(ncnt+j,ncnt+j+1,inf,Dt[i+1].ft-Dt[i].ft);
		Add_Edge(ncnt+j+1,ncnt+j,inf,Dt[i+1].ft-Dt[i].ft);
	}
	//cout<<"["<<l<<" "<<mid<<" "<<r<<"] "<<ncnt+1<<" "<<ncnt+mid-l+1<<endl;
	//for (int i=l;i<=mid;i++) cout<<"("<<Dt[i].ft<<" "<<Dt[i].sd<<") ";cout<<endl;
	for (int i=mid+1,p=l-1,j=0; i<=r; i++) {
		while (p<mid&&Dt[p+1].ft<=Dt[i].ft) ++p,++j;
		//cout<<i<<":"<<Dt[i].ft<<" "<<Dt[i].sd<<" "<<p<<endl;
		if (p>=l) Add_Edge(Dt[i].sd,ncnt+j,1,Dt[i].ft-Dt[p].ft);
		if (p<mid) Add_Edge(Dt[i].sd,ncnt+j+1,1,Dt[p+1].ft-Dt[i].ft);
	}
	//*/
	ncnt+=(mid-l+1);
	sort(&Dt[l],&Dt[r+1]);
	//cout<<"("<<l<<" "<<r<<"):";
	//for (int i=l;i<=r;i++) cout<<Dt[i].ft<<" "<<Dt[i].sd<<" | ";cout<<endl;
	return;
}
bool spfa()
{
	static bool inq[maxNN];
	static queue<int> Qu;
	Qu.push(S);
	memset(D,127,sizeof(D));
	D[S]=0;
	bool checkT=0;
	while (!Qu.empty()) {
		int u=Qu.front();
		Qu.pop();
		if (u==T) checkT=1;
		for (int i=Hd[u]; i!=-1; i=Nt[i])
			if (E[i].flow&&D[E[i].v]>D[u]+E[i].w) {
				D[E[i].v]=D[u]+E[i].w;
				Path[E[i].v]=i;
				if (inq[E[i].v]==0) {
					inq[E[i].v]=1;
					Qu.push(E[i].v);
				}
			}
		inq[u]=0;
	}
	return checkT;
}
