#include<bits/stdc++.h>
using namespace std;

const int maxN=1010;

int n,m;
double X[maxN],Y[maxN];

int main(){
    freopen("in","r",stdin);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%lf",&X[i]);
    for (int i=1;i<=n;i++) scanf("%lf",&Y[i]);

    while (m--){
	int opt,l,r,s,t;scanf("%d%d%d",&opt,&l,&r);
	if (opt>=2) scanf("%d%d",&s,&t);
	if (opt==1){
	    double x=0,y=0,sz=r-l+1;for (int i=l;i<=r;i++) x+=X[i],y+=Y[i];
	    x/=sz;y/=sz;
	    cout<<sz<<" "<<x<<" "<<y<<endl;
	    double up=0,down=0;for (int i=l;i<=r;i++) up+=(X[i]-x)*(Y[i]-y),down+=(X[i]-x)*(X[i]-x);
	    printf("%.10lf\n",up/down);
	}
	if (opt==2) for (int i=l;i<=r;i++) X[i]+=s,Y[i]+=t;
	if (opt==3) for (int i=l;i<=r;i++) X[i]=s+i,Y[i]=t+i;
    }
    return 0;
}
