#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

const int maxN=101000;
const int maxM=maxN*5;
const int maxQ=maxN;
const int inf=2000000000;

class Option
{
public:
	int opt,l,r,x;
};

int n,m;
int edgecnt=-1,Hd[maxN],Nt[maxM],V[maxM],W[maxM];
int Dst[maxN],inq[maxN],Ans[maxN];
int Qu[maxQ];
Option O[maxN];

void Add_Edge(int u,int v,int w);
int main()
{
	//freopen("in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) scanf("%d%d%d%d",&O[i].opt,&O[i].l,&O[i].r,&O[i].x);
	for (int b=0; b<20; b++) {
		edgecnt=-1;
		memset(Hd,-1,sizeof(Hd));
		memset(Dst,0,sizeof(Dst));
		for (int i=0; i<n; i++) Add_Edge(i+1,i,0),Add_Edge(i,i+1,1);
		for (int i=1; i<=m; i++) {
			int l=O[i].l,r=O[i].r;
			if (O[i].opt==1) {
				if ((O[i].x>>b)&1) Add_Edge(r,l-1,-1);
				else Add_Edge(l-1,r,0),++Dst[l],--Dst[r+1];
			} else {
				if ((O[i].x>>b)&1) Add_Edge(r,l-1,-(r-l+1));
				else Add_Edge(l-1,r,r-l);
			}
		}
		for (int i=1; i<=n; i++) Dst[i]+=Dst[i-1];
		for (int i=1; i<=n; i++) Dst[i]=(Dst[i]==0);
		for (int i=1; i<=n; i++) Dst[i]+=Dst[i-1];
		int ql=1,qr=1;
		for (int i=0; i<=n; i++) Qu[++qr]=i,inq[i]=1;
		while (ql!=qr) {
			++ql;
			ql%=maxQ;
			int u=Qu[ql];
			for (int i=Hd[u]; i!=-1; i=Nt[i])
				if (Dst[V[i]]>Dst[u]+W[i]) {
					Dst[V[i]]=Dst[u]+W[i];
					if (inq[V[i]]==0) {
						++qr;
						qr%=maxQ;
						Qu[qr]=V[i];
						inq[V[i]]=1;
					}
				}
			inq[u]=0;
		}
		//for (int i=0;i<=n;i++) cout<<Dst[i]<<" ";cout<<endl;
		for (int i=1; i<=n; i++) if (Dst[i]-Dst[i-1]) Ans[i]|=(1<<b);
	}
	for (int i=1; i<=n; i++) printf("%d ",Ans[i]);
	return 0;
}
void Add_Edge(int u,int v,int w)
{
	//cout<<u<<"->"<<v<<" "<<w<<endl;
	Nt[++edgecnt]=Hd[u];
	Hd[u]=edgecnt;
	V[edgecnt]=v;
	W[edgecnt]=w;
	return;
}