#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ps push
#define mp make_pair
#define ft first
#define sd second

const int maxN=202000;
const int inf=2000000000;

class Question
{
public:
	int x1,y1,x2,y2;
};

int n,m,Q,Ans[maxN];
vector<int> W1[maxN],W2[maxN],D[maxN],vis[maxN];
Question Qs[maxN];
int Qn[maxN],Bp[maxN],St[maxN];
pair<int,int> Qu[maxN];
priority_queue<pair<int,pair<int,int> > > H;

void Divide(int xl,int xr,int yl,int yr,int ql,int qr);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) W1[i].resize(m+2),W2[i].resize(m+2),D[i].resize(m+2),vis[i].resize(m+2);
	for (int i=1; i<=n; i++) for (int j=1; j<m; j++) scanf("%d",&W1[i][j]);
	for (int i=1; i<n; i++) for (int j=1; j<=m; j++) scanf("%d",&W2[i][j]);
	scanf("%d",&Q);
	for (int i=1; i<=Q; i++) scanf("%d%d%d%d",&Qs[i].x1,&Qs[i].y1,&Qs[i].x2,&Qs[i].y2),Qn[i]=i,Ans[i]=inf;
	Divide(1,n,1,m,1,Q);
	for (int i=1; i<=Q; i++) printf("%d\n",Ans[i]);
	return 0;
}

void Divide(int xl,int xr,int yl,int yr,int ql,int qr)
{
	int top=0;
	if (xr-xl>=yr-yl) {
		int mid=(xl+xr)>>1;
		for (int i=yl; i<=yr; i++) Qu[++top]=mp(mid,i);
	} else {
		int mid=(yl+yr)>>1;
		for (int i=xl; i<=xr; i++) Qu[++top]=mp(i,mid);
	}
	while (top) {
		int dx=Qu[top].ft,dy=Qu[top].sd;
		--top;
		for (int i=xl; i<=xr; i++) for (int j=yl; j<=yr; j++) D[i][j]=inf,vis[i][j]=0;
		D[dx][dy]=0;
		H.ps(mp(0,mp(dx,dy)));
		while (!H.empty()) {
			int x=H.top().sd.ft,y=H.top().sd.sd;
			H.pop();
			if (vis[x][y]) continue;
			vis[x][y]=1;
			if (x+1<=xr&&D[x+1][y]>D[x][y]+W2[x][y]) H.ps(mp(-(D[x+1][y]=D[x][y]+W2[x][y]),mp(x+1,y)));
			if (y+1<=yr&&D[x][y+1]>D[x][y]+W1[x][y]) H.ps(mp(-(D[x][y+1]=D[x][y]+W1[x][y]),mp(x,y+1)));
			if (x-1>=xl&&D[x-1][y]>D[x][y]+W2[x-1][y]) H.ps(mp(-(D[x-1][y]=D[x][y]+W2[x-1][y]),mp(x-1,y)));
			if (y-1>=yl&&D[x][y-1]>D[x][y]+W1[x][y-1]) H.ps(mp(-(D[x][y-1]=D[x][y]+W1[x][y-1]),mp(x,y-1)));
		}
		for (int i=ql; i<=qr; i++) {
			int j=Qn[i];
			Ans[j]=min(Ans[j],D[Qs[j].x1][Qs[j].y1]+D[Qs[j].x2][Qs[j].y2]);
		}
	}
	if (xr-xl>=yr-yl) {
		int mid=(xr+xl)>>1;
		int ml=ql-1,mr=qr+1;
		for (int i=ql; i<=qr; i++) {
			int j=Qn[i];
			if ((Qs[j].x1<mid)&&(Qs[j].x2<mid)) Bp[++ml]=j;
			else if ((Qs[j].x1>mid)&&(Qs[j].x2>mid)) Bp[--mr]=j;
		}
		for (int i=ql; i<=qr; i++) Qn[i]=Bp[i];
		if (ml>=ql) Divide(xl,mid-1,yl,yr,ql,ml);
		if (mr<=qr) Divide(mid+1,xr,yl,yr,mr,qr);
	} else {
		int mid=(yl+yr)>>1;
		int ml=ql-1,mr=qr+1;
		for (int i=ql; i<=qr; i++) {
			int j=Qn[i];
			if ((Qs[j].y1<mid)&&(Qs[j].y2<mid)) Bp[++ml]=j;
			else if ((Qs[j].y1>mid)&&(Qs[j].y2>mid)) Bp[--mr]=j;
		}
		for (int i=ql; i<=qr; i++) Qn[i]=Bp[i];
		if (ml>=ql) Divide(xl,xr,yl,mid-1,ql,ml);
		if (mr<=qr) Divide(xl,xr,mid+1,yr,mr,qr);
	}
	return;
}
