#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define REP(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define DREP(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
#define EREP(i,a) for(int i=start[(a)];i;i=e[i].next)
template<class T>inline void chkmax(T &a,T b){ if(a<b)a=b;}
template<class T>inline void chkmin(T &a,T b){ if(a>b)a=b;}
#define fi first
#define se second
#define mkr(a,b) make_pair(a,b)
inline int read()
{
	int sum=0,p=1;char ch=getchar();
	while(!(('0'<=ch && ch<='9') || ch=='-'))ch=getchar();
	if(ch=='-')p=-1,ch=getchar();
	while('0'<=ch && ch<='9')sum=sum*10+ch-48,ch=getchar();
	return sum*p;
}

const int maxn=2e5+20;
const ll inf=1e8;

int a[maxn],x[maxn],y[maxn],n,as[maxn];
int xs[maxn],ys[maxn];
int L[maxn],R[maxn];

int main()
{
	n=read();
	REP(i,1,n)a[i]=read(),x[i]=~a[i]&1,y[i]=a[i]<=2?2-a[i]:(a[i]&1);
	REP(i,1,n)xs[i]=xs[i-1]+x[i],ys[i]=ys[i-1]+y[i],as[i]=as[i-1]+a[i];
	L[0]=0;
	int mn=0;
	REP(i,1,n)
	{
		chkmin(mn,as[i]-ys[i]);
		L[i]=mn+ys[i];
	}
	R[n]=0;
	mn=as[n]-as[n] + ys[n];
	DREP(i,n-1,0)
	{
		chkmin(mn,as[n]-as[i]+ys[i]);
		R[i]=mn-ys[i];
    }
  for(int i=1;i<=n;i++) cout<<L[i]<<" ";cout<<endl;
  for (int i=1;i<=n;i++) cout<<R[i]<<" ";cout<<endl;
	int ans=inf;
	mn=inf;
	REP(i,0,n)
	{
		chkmin(mn,L[i]-xs[i]);
		chkmin(ans,mn+R[i]+xs[i]);
	}
	printf("%d\n",ans);
    return 0;
}
