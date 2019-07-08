#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000;
const int maxM=maxN<<1;

class EDGE
{
public:
	int ecnt,Hd[maxN],Nt[maxM],V[maxM];
	EDGE()
	{
		ecnt=-1;
		memset(Hd,-1,sizeof(Hd));
	}
	void Add_Edge(int u,int v)
	{
		Nt[++ecnt]=Hd[u];
		Hd[u]=ecnt;
		V[ecnt]=v;
		return;
	}
};

int n,m,S,A,B;
EDGE E1,E2;
int Qu[maxN],label[maxN],Ans[maxN],Mark[maxN];

int main()
{
	scanf("%d%d%d%d%d",&n,&m,&S,&A,&B);
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		E1.Add_Edge(u,v);
		E1.Add_Edge(v,u);
		E2.Add_Edge(u,v);
		E2.Add_Edge(v,u);
	}
	memset(label,-1,sizeof(label));
	int ql=1,qr=1;
	label[Qu[1]=S]=0;
	while (ql<=qr) for (int u=Qu[ql++],i=E1.Hd[u]; i!=-1; i=E1.Nt[i]) if (label[E1.V[i]]==-1) label[Qu[++qr]=E1.V[i]]=label[u]+1;
	for (int i=1; i<=n; i++) Ans[i]=min(label[i]*A,label[i]/2*B+(label[i]&1)*A);
	memset(label,-1,sizeof(label));
	label[Qu[ql=qr=1]=S]=0;
	while (ql<=qr) {
		int u=Qu[ql++];
		for (int i=E1.Hd[u]; i!=-1; i=E1.Nt[i]) Mark[E1.V[i]]=1;
		for (int i=E1.Hd[u]; i!=-1; i=E1.Nt[i])
			for (int j=E2.Hd[E1.V[i]],lst=-1; j!=-1; j=E2.Nt[j])
				if (label[E2.V[j]]==-1&&!Mark[E2.V[j]]) {
					label[Qu[++qr]=E2.V[j]]=label[u]+1;
					if (lst==-1) E2.Hd[E1.V[i]]=E2.Nt[j];
					else E2.Nt[lst]=E2.Nt[j];
				} else lst=j;
		for (int i=E1.Hd[u]; i!=-1; i=E1.Nt[i]) Mark[E1.V[i]]=0;
	}
	for (int i=1; i<=n; i++) if (label[i]!=-1) Ans[i]=min(Ans[i],label[i]*B);
	for (int i=1; i<=n; i++) printf("%d\n",Ans[i]);
	return 0;
}
