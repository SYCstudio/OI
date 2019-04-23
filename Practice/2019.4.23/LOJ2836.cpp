#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxN=505000;
const ll INF=1e18;
const ll Mx=1e10;

int n,Q;
int D[maxN];
ll B1[maxN],B2[maxN];

int main(){
    scanf("%d%d",&n,&Q);for (int i=1;i<=n;i++) scanf("%d",&D[i]);
    B1[0]=1;B2[0]=1;
    for (int i=1;i<=n;i++){
	ll t=(D[i]+B2[i-1]-1)/B2[i-1];
	B1[i]=t*B1[i-1];B2[i]=t*B2[i-1];
    }
    //for (int i=1;i<=n;i++) printf("%lld %lld\n",B1[i],B2[i]);
    while (Q--){
	int L,R,T;scanf("%d%d%d",&T,&L,&R);
	int p1=-1,p2=-1,l=0,r=n;
	//for (int i=0;i<=n;i++) printf("%lld ",T/B1[i]*B2[i]-i);printf("\n");
	while (l<=r){
	    int mid=(l+r)>>1;
	    if (T/B1[mid]*B2[mid]-mid<=R) p1=mid,r=mid-1;
	    else l=mid+1;
	}
	l=0;r=n;
	while (l<=r){
	    int mid=(l+r)>>1;
	    if (T/B1[mid]*B2[mid]-mid>=L) p2=mid,l=mid+1;
	    else r=mid-1;
	}
	if (p1==-1||p2==-1) puts("0");
	else printf("%d\n",p2-p1+1);
    }
    return 0;
}
